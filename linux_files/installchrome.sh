#!/bin/bash
wget -q -O - https://dl.google.com/linux/linux_signing_key.pub | sudo apt-key add -
rm linux_signing_key.pub
sudo sh -c 'echo "deb http://dl.google.com/linux/chrome/deb/ stable main " > /etc/apt/sources.list.d/googlechrome.list'
sudo apt update
sudo apt install google-chrome-stable