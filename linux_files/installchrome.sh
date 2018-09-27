#!/bin/bash 

CURDIR=$(pwd)
TMPDIR=$(mktemp -d)
cd $TMPDIR

wget -q -O - https://dl.google.com/linux/linux_signing_key.pub | sudo apt-key add - 
sudo sh -c 'echo "deb http://dl.google.com/linux/chrome/deb/ stable main " > /etc/apt/sources.list.d/googlechrome.list' 
sudo apt upgrade -y 
sudo apt update -y  
sudo apt install google-chrome-stable

cd $CURDIR
rm -r $TMPDIR
