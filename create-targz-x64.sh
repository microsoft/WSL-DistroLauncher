#!/bin/bash

# install script dependencies
sudo apt update
sudo apt -y install curl gnupg cdebootstrap

# create our environment
set -e
BUILDIR=$(pwd)
TMPDIR=$(mktemp -d)
ARCH="amd64"
DIST="stable"
cd $TMPDIR

# bootstrap image
sudo cdebootstrap -a $ARCH --include=sudo,locales,git,apt-transport-https,wget,ca-certificates,man,less,xclip,gnome-themes-standard,gtk2-engines-murrine,dbus-x11,zsh $DIST $DIST http://deb.debian.org/debian

# clean apt cache
sudo chroot $DIST apt-get clean

# configure bash
sudo chroot $DIST /bin/bash -c "echo 'en_US.UTF-8 UTF-8' >> /etc/locale.gen && locale-gen"
sudo chroot $DIST /bin/bash -c "update-locale LANGUAGE=en_US.UTF-8 LC_ALL=C"

# download and copy latest wslu repo key
curl https://api.patrickwu.ml/public.key | gpg --dearmor > $BUILDIR/wslu.gpg
sudo cp $BUILDIR/wslu.gpg $TMPDIR/$DIST/etc/apt/trusted.gpg.d/wslu.gpg
rm $BUILDIR/wslu.gpg

# copy custom files to image
sudo cp $BUILDIR/linux_files/profile $TMPDIR/$DIST/etc/profile
sudo cp $BUILDIR/linux_files/os-release $TMPDIR/$DIST/etc/os-release
sudo cp $BUILDIR/linux_files/sources.list $TMPDIR/$DIST/etc/apt/sources.list
sudo cp $BUILDIR/linux_files/preferences $TMPDIR/$DIST/etc/apt/preferences

# copy app installer scripts to image
sudo cp $BUILDIR/linux_files/installchrome.sh $TMPDIR/$DIST/opt/installchrome.sh
sudo cp $BUILDIR/linux_files/installcode.sh $TMPDIR/$DIST/opt/installcode.sh

# make app installer scripts executable
sudo chroot $DIST chmod u+x /opt/installchrome.sh
sudo chroot $DIST chmod u+x /opt/installcode.sh

# install python 3.7 from testing
sudo chroot $DIST apt update
sudo chroot $DIST apt -t testing install python3.7 -y

# set up the latest wslu app
sudo chroot $DIST chmod 644 /etc/apt/trusted.gpg.d/wslu.gpg
sudo chroot $DIST apt update
sudo chroot $DIST apt -y install wslu

# remove unnecessary apt packages
sudo chroot $DIST apt remove systemd dmidecode -y --allow-remove-essential

# clean up orphaned apt dependencies
sudo chroot $DIST apt-get autoremove -y

# create tar
cd $DIST
sudo tar --ignore-failed-read -czvf $TMPDIR/install.tar.gz *

# move into place in build folder
cd $TMPDIR
cp install.tar.gz $BUILDIR/x64/
cd $BUILDIR

# cp install.tar.gz /mnt/c/Users/Hayden/OneDrive/Documents/GitHub/WLinux/x64/
