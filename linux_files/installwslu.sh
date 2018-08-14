#!/bin/bash
# copied from https://github.com/patrick330602/wslu
# see also install script https://github.com/patrick330602/wslu/blob/master/scripts/install.sh
sudo apt install lsb-release apt-transport-https
wget -O - https://api.patrickwu.ml/public.key | sudo apt-key add -
sudo echo "deb https://apt.patrickwu.ml/ `lsb_release -c -s` main" >> /etc/apt/sources.list 
sudo apt update
