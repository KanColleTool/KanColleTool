#!/bin/bash
# $1 is distro $2 is ppa address 

VERSION=$(<VERSION)

# Prepare source tarballs for build
./linbuild.sh ppa$1~$2

# Make packages
./linbuild-ppa.sh $2

cd dist/ppa/$2
dput $3 kancolletool_${VERSION}*_source.changes
dput $3 kancolletool-viewer_${VERSION}*_source.changes
