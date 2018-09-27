#!/bin/bash 
CURDIR=$(pwd)
TMPDIR=$(mktemp -d)
cd $TMPDIR

sudo apt-get install apt-transport-https curl -y 
curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg 
sudo mv microsoft.gpg /etc/apt/trusted.gpg.d/microsoft.gpg 
sudo sh -c 'echo "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list' 
sudo apt upgrade -y 
sudo apt update -y 
sudo apt install code libxss1 libasound2

cd $CURDIR
rm -r $TMPDIR
