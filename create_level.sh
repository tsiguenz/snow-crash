#/bin/bash

mkdir -p level$1/ressources
touch level$1/flag
touch level$1/ressources/README.md
cd level$1
vim flag ressources/README.md
