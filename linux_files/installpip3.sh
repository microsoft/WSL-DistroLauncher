#!/bin/bash
sudo apt update
sudo apt upgrade -y
sudo apt install curl
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py --user
export PATH="$PATH:/home/~/.local/bin"
echo 'export PATH="$PATH:/home/~/.local/bin"' >> ~/.bashrc
pip install -U pip
echo "Done"
