package main

import (
	"bytes"
	"encoding/csv"
	"errors"
	"fmt"
	"image"
	_ "image/png"
	"io/fs"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
	"strings"
	"text/template"

	"github.com/spf13/cobra"
	"gopkg.in/gographics/imagick.v2/imagick"
)

/*
   release-template creates a new release content and assets if we have a new release or version

ver.	m.	code	full version	Status				Activ.	Sup.	LTS		Opened			Release			Milestone
21.10	0	impish	Ubuntu 21.10	Active Development	True	False	False	2021-04-23
21.04	0	hirsute	Ubuntu 21.04	Current Stable Release	True	True	False	2020-10-23	2021-04-22
20.10	0	groovy	Ubuntu 20.10	Supported	True	True	False	2020-04-24	2020-10-22
20.04	2	focal	Ubuntu 20.04.2 LTS	Supported	True	True	True	2019-02-18	2020-04-23	2021-02-11
18.04	5	bionic	Ubuntu 18.04.5 LTS	Supported	True	True	True	2017-10-04	2018-04-26	2020-08-06
16.04	6	xenial	Ubuntu 16.04.6 LTS	Supported	True	True	True	2015-10-19	2016-04-21	2019-02-28
14.04	6	trusty	Ubuntu 14.04.6 LTS	Supported	True	True	True	2012-10-01	2014-04-17	2019-03-07

WSL_ID                      FULLNAME                    BUILD_VERSION      LAUNCHER_NAME             ICON_VERSION                BUILD_ID (locally stored, incremental)
Ubuntu                      Ubuntu                      2004.2             ubuntu                    ""
Ubuntu-Preview              Ubuntu (Preview)            2110.0             ubuntupreview             Preview
Ubuntu-20.04-LTS            Ubuntu 20.04.2 LTS          2004.2             ubuntu2004                20.04.2 LTS
Ubuntu-18.04-LTS            Ubuntu 18.04.5 LTS          1804.5             ubuntu1804                18.04.5 LTS

*/

func main() {
	rootCmd := &cobra.Command{
		Use:   "update-releases CSV_RELEASE_FILE",
		Short: "Update releases in WSL distribution info and assets from template",
		Long: `This tool update releases from an incoming CSV file and generate
		       every icons and xml files needed to build a WSL application`,
		RunE: func(cmd *cobra.Command, args []string) error {
			if len(args) != 1 {
				return errors.New("this command accepts exactly one CSV file")
			}

			return updateReleases(args[0])
		},
	}

	err := rootCmd.Execute()
	if err != nil {
		log.Fatal(err)
	}
}

// updateReleases orchestrates the distro launcher metadata and assets generation from a csv file path.
func updateReleases(csvPath string) error {
	imagick.Initialize()
	defer imagick.Terminate()

	releases, err := readCSV(csvPath)
	if err != nil {
		return err
	}

	rootPath, err := getPathWith("DistroLauncher-Appx")
	if err != nil {
		return err
	}
	rootPath = filepath.Dir(rootPath)
	metaPath, err := getPathWith("meta")
	if err != nil {
		return err
	}

	wslReleases := activeReleases(releases)
	releasesInfo := buildReleasesInfo(wslReleases)

	// Update each release
	for _, r := range releasesInfo {
		// Reset directory
		wslPath := filepath.Join(metaPath, r.WslID)
		if err := os.RemoveAll(wslPath); err != nil {
			return err
		}
		if err := os.MkdirAll(wslPath, 0755); err != nil {
			return err
		}

		if err := generateMetaFilesForRelease(r, wslPath, rootPath); err != nil {
			return err
		}

		if err := generateAssetsForRelease(r, wslPath, metaPath, rootPath); err != nil {
			return err
		}
	}

	return nil
}

// readCSV deserialized the CSV filed into a [][]string
func readCSV(name string) (releases [][]string, err error) {
	defer func() {
		if err != nil {
			err = fmt.Errorf("can't read CSV file: %v", err)
		}
	}()

	// Read CSV file
	f, err := os.Open(name)
	if err != nil {
		return nil, err
	}
	r := csv.NewReader(f)
	r.Comma = '\t'
	return r.ReadAll()
}

// activeReleases extracts WSL supported releases from the releases content
// and returns a map of WslID to version string.
func activeReleases(releases [][]string) (wslReleases map[string]string) {
	wslReleases = make(map[string]string)
	var latestLTS, latestLTSReleasedDate string

	for _, release := range releases {
		switch release[4] {
		case "Active Development":
			wslReleases["Ubuntu-Preview"] = fmt.Sprintf("%s.0", release[0])
		case "Supported":
			// WSL is only supported on 18.04 LTSes and onward
			if release[7] != "True" || release[0] < "18.04" {
				continue
			}
			wslID := fmt.Sprintf("Ubuntu-%s-LTS", release[0])
			wslReleases[wslID] = fmt.Sprintf("%s.%s", release[0], release[1])
			if release[9] > latestLTSReleasedDate {
				latestLTSReleasedDate = release[9]
				latestLTS = wslID
			}
		}
	}
	wslReleases["Ubuntu"] = wslReleases[latestLTS]

	return wslReleases
}

type wslReleaseInfo struct {
	WslID        string
	FullName     string
	BuildVersion string
	LauncherName string
	IconVersion  string
}

// buildReleasesInfo returns a slice of release info object, ready to be used
// in templates.
func buildReleasesInfo(releases map[string]string) (releasesInfo []wslReleaseInfo) {
	// Ubuntu-Preview              Ubuntu (Preview)            2110.0             ubuntupreview             Preview
	// Ubuntu-20.04-LTS            Ubuntu 20.04.2 LTS          2004.2             ubuntu2004                20.04.2 LTS
	for wslID, version := range releases {
		var fullName, iconVersion string
		switch wslID {
		case "Ubuntu":
			fullName = "Ubuntu"
		case "Ubuntu-Preview":
			fullName = "Ubuntu (Preview)"
			iconVersion = "Preview"
		default:
			fullName = fmt.Sprintf("Ubuntu %s LTS", version)
			iconVersion = fmt.Sprintf("%s LTS", version)
		}

		releasesInfo = append(releasesInfo, wslReleaseInfo{
			WslID:    wslID,
			FullName: fullName,
			// buildVersion is the version with first . stripped out
			BuildVersion: strings.Replace(version, ".", "", 1),
			LauncherName: strings.TrimSuffix(strings.ReplaceAll(strings.ReplaceAll(strings.ToLower(wslID), "-", ""), ".", ""), "lts"),
			IconVersion:  iconVersion,
		})
	}

	return releasesInfo
}

// getPathWith return the parent directory containing subdirectory. It goes up from
// current working directory.
func getPathWith(subdirectory string) (metaDir string, err error) {
	defer func() {
		if err != nil {
			err = fmt.Errorf("couldn't find a %s directory: %v", subdirectory, err)
		}
	}()

	current, err := os.Getwd()
	if err != nil {
		return "", err
	}

	for current != "/" {
		if _, err := os.Stat(filepath.Join(current, subdirectory)); err == nil {
			return filepath.Join(current, subdirectory), nil
		}
		current = filepath.Dir(current)
	}

	return "", errors.New("nothing found until /")
}

// generateMetaFilesForRelease updates all metadata files from template for a given release.
func generateMetaFilesForRelease(r wslReleaseInfo, wslPath, rootPath string) (err error) {
	defer func() {
		if err != nil {
			err = fmt.Errorf("can't generate metadata file for %s: %v", r.WslID, err)
		}
	}()

	// Fetch all templated files and recreate them (and intermediate directories)
	err = filepath.WalkDir(rootPath, func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			return err
		}

		relPath := strings.TrimPrefix(path, rootPath+"/")
		if !strings.HasPrefix(relPath, "DistroLauncher/") && !strings.HasPrefix(relPath, "DistroLauncher-Appx/") {
			return nil
		}
		if d.IsDir() {
			return nil
		}

		// ensure we have template file to substitude data in
		data, err := os.ReadFile(path)
		if err != nil {
			return err
		}
		templateData := string(data)
		if !strings.Contains(templateData, "{{.") {
			return nil
		}

		destPath := filepath.Join(wslPath, relPath)
		if err := os.MkdirAll(filepath.Dir(destPath), 0755); err != nil {
			return err
		}

		t := template.Must(template.New("").Parse(templateData))

		f, err := os.Create(destPath)
		if err != nil {
			return nil
		}
		defer f.Close()

		return t.Execute(f, r)
	})
	return err
}

// generateAssetsForRelease updates all assets files from template for a given release.
func generateAssetsForRelease(r wslReleaseInfo, wslPath, metaPath, rootPath string) (err error) {
	// Iterates and generates over assets
	assetsRelDir := filepath.Join("DistroLauncher-Appx", "Assets")
	assetsPath := filepath.Join(rootPath, assetsRelDir)
	images, err := ioutil.ReadDir(assetsPath)
	if err != nil {
		return err
	}

	mwTemplates := make(map[string]*imagick.MagickWand)
	for _, f := range images {
		// 1. Load size of the ressource image
		srcF, err := os.Open(filepath.Join(assetsPath, f.Name()))
		if err != nil {
			return err
		}
		defer srcF.Close()

		src, _, err := image.DecodeConfig(srcF)
		if err != nil {
			return err
		}

		// 2. Compute template name
		templateName := filepath.Base(f.Name())
		templateName = strings.Split(templateName, ".")[0]
		if strings.Contains(f.Name(), "altform-unplated") {
			templateName = fmt.Sprintf("%s.altform-unplated", templateName)
		}
		templatePath := filepath.Join(metaPath, "images", fmt.Sprintf("%s.svg", templateName))

		// 3. Replace any version id if present
		templateData, err := os.ReadFile(templatePath)
		if err != nil {
			return err
		}
		t := template.Must(template.New("").Parse(string(templateData)))
		var templateBuf bytes.Buffer
		if err := t.Execute(&templateBuf, r); err != nil {
			return err
		}

		// 4. Rescale
		// Reuse existing templates
		mw, exists := mwTemplates[templateName]
		if !exists {
			mw = imagick.NewMagickWand()
			defer mw.Destroy()
			if err := mw.ReadImageBlob(templateBuf.Bytes()); err != nil {
				return err
			}
			mwTemplates[templateName] = mw
		}
		mw = mw.Clone()
		defer mw.Destroy()

		if err := mw.ResizeImage(uint(src.Width), uint(src.Height), imagick.FILTER_LANCZOS, 1); err != nil {
			return err
		}
		if err := mw.SetImageCompressionQuality(95); err != nil {
			return err
		}

		assetsDest := filepath.Join(wslPath, assetsRelDir, f.Name())
		if err := os.MkdirAll(filepath.Dir(assetsDest), 0755); err != nil {
			return err
		}
		if err := mw.WriteImage(assetsDest); err != nil {
			return err
		}
	}

	// Icon files
	tmpDir, err := os.MkdirTemp("", "update-releases-*")
	if err != nil {
		return err
	}
	defer os.RemoveAll(tmpDir)
	src := filepath.Join(tmpDir, "icon.svg")
	srcF, err := os.Create(src)
	if err != nil {
		return err
	}
	defer srcF.Close()

	srcIconPath := filepath.Join(metaPath, "images", "icon.svg")
	templateData, err := os.ReadFile(srcIconPath)
	if err != nil {
		return err
	}
	t := template.Must(template.New("").Parse(string(templateData)))
	if err := t.Execute(srcF, r); err != nil {
		return err
	}
	srcF.Close()

	dest := filepath.Join(wslPath, "DistroLauncher", "images", "icon.ico")
	if err := os.MkdirAll(filepath.Dir(dest), 0755); err != nil {
		return err
	}

	_, err = imagick.ConvertImageCommand([]string{
		"convert", src, "-resize", "256x256", "-define",
		"icon:auto-resize=16,32,48,256",
		dest,
	})
	return err
}
