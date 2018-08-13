#!/bin/bash
# install script dependencies
sudo apt install curl gpg cdebootstrap
# create our environment
set -e
BUILDIR=$(pwd)
TMPDIR=$(mktemp -d)
ARCH="amd64"
DIST="stable"
cd $TMPDIR
sudo cdebootstrap -a $ARCH --include=sudo,locales,git,python3 $DIST $DIST http://deb.debian.org/debian
# clean up apt cache
sudo chroot $DIST apt-get clean
# configure bash
sudo chroot $DIST /bin/bash -c "echo 'en_US.UTF-8 UTF-8' >> /etc/locale.gen && locale-gen"
sudo chroot $DIST /bin/bash -c "update-locale LANGUAGE=en_US.UTF-8 LC_ALL=C"
# copy custom files to image
sudo cp $BUILDIR/linux_files/profile $TMPDIR/$DIST/etc/profile
sudo cp $BUILDIR/linux_files/os-release $TMPDIR/$DIST/etc/os-release
sudo cp $BUILDIR/linux_files/sources.list $TMPDIR/$DIST/etc/apt/sources.list
# copy installer scripts to image
sudo cp $BUILDIR/linux_files/installchrome.sh $TMPDIR/$DIST/opt/installchrome.sh
sudo cp $BUILDIR/linux_files/installcode.sh $TMPDIR/$DIST/opt/installcode.sh
# make installer scripts executable
sudo chroot $DIST chmod u+x /opt/installchrome.sh
sudo chroot $DIST chmod u+x /opt/installcode.sh
# remove unnecessary packages
sudo chroot $DIST apt remove iptables -y
# clean up orphaned dependencies
sudo chroot $DIST apt-get autoremove -y
# create tar
cd $DIST
sudo tar --ignore-failed-read -czvf $TMPDIR/install.tar.gz *
# move to build directory
cp $TMPDIR/install.tar.gz $BUILDIR
cd $BUILDIR