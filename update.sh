#!/bin/bash

# Update QMK
pushd qmk/qmk_firmware || exit
git fetch
# TODO: use renovate to get this updated to the latest version
git checkout "$(git describe --tags --abbrev=0 origin/master)"
qmk git-submodule
popd || exit

# Update getreuer
pushd qmk/modules/getreuer || exit
git pull
popd || exit
