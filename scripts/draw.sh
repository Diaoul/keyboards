#!/bin/bash

# Corne
qmk c2json -kb splitkb/aurora/corne -km diaoul --no-cpp qmk/keyboards/splitkb/aurora/corne/keymaps/diaoul/keymap.c \
  | keymap -c keymap-drawer.yaml parse --layer-names Base Sym Num Nav Fun -c 10 -q - \
  | keymap -c keymap-drawer.yaml draw - > docs/corne-keymap.svg
