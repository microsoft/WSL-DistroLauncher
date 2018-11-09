#!/bin/bash

# install script dependencies
sudo apt update
sudo apt -y install curl gnupg cdebootstrap

# create our environment
set -e
BUILDIR=$(pwd)
TMPDIR=$(mktemp -d)
ARCH="amd64"
DIST="testing"
cd $TMPDIR

# bootstrap image
sudo cdebootstrap -a $ARCH --include=sudo,locales,git,ssh,apt-transport-https,wget,ca-certificates,man,less,curl $DIST $DIST http://deb.debian.org/debian

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
sudo cp $BUILDIR/linux_files/environment $TMPDIR/$DIST/etc/environment
sudo cp $BUILDIR/linux_files/os-release $TMPDIR/$DIST/etc/os-release
sudo cp $BUILDIR/linux_files/sources.list $TMPDIR/$DIST/etc/apt/sources.list
sudo cp $BUILDIR/linux_files/preferences $TMPDIR/$DIST/etc/apt/preferences
sudo cp $BUILDIR/linux_files/wsl.conf $TMPDIR/$DIST/etc/wsl.conf
sudo cp $BUILDIR/linux_files/default $TMPDIR/$DIST/etc/dpkg/origins/default
sudo mkdir $TMPDIR/$DIST/etc/fonts
sudo cp $BUILDIR/linux_files/local.conf $TMPDIR/$DIST/etc/fonts/local.conf
sudo cp $BUILDIR/linux_files/helpme $TMPDIR/$DIST/etc/helpme
sudo cp $BUILDIR/linux_files/setup $TMPDIR/$DIST/etc/setup

#make helpme and setup executable
sudo chroot $DIST chmod 755 /etc/helpme
sudo chroot $DIST chmod 755 /etc/setup

# set up the latest wslu app
sudo chroot $DIST chmod 644 /etc/apt/trusted.gpg.d/wslu.gpg
sudo chroot $DIST apt update
sudo chroot $DIST apt -y install wslu

# the sudoers lecture is one of the first things users see when they run /etc/setup, it is a bit jarring, and a bit out of place on WSL, so let's make it a bit more friendly

sudo chroot $DIST /bin/bash -c "echo 'Defaults lecture_file = /etc/sudoers.lecture' >> /etc/sudoers"
sudo chroot $DIST /bin/bash -c "echo 'Enter your UNIX password below. This is not your Windows password.' >> /etc/sudoers.lecture"

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
