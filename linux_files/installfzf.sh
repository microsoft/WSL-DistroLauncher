#!/bin/bash

set -e
TMPDIR=$(mktemp -d)
cd $TMPDIR

git clone --depth 1 https://github.com/junegunn/fzf.git
cd fzf
./install

# For more information, see: https://github.com/junegunn/fzf   
