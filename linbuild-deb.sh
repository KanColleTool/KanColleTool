#!/bin/bash

# This both puts the sources in the right place and gives us $VERSION
source linbuild.sh

# Make .orig tarballs, since debian's helper scripts really like that name
cd dist
cp kancolletool-${VERSION}.tar.gz kancolletool_${VERSION}.orig.tar.gz
cp kancolletool-viewer-${VERSION}.tar.gz kancolletool-viewer_${VERSION}.orig.tar.gz

# Debianize and package the Tool
cd kancolletool-${VERSION}/
cp -R ../../targets/debian/kancolletool/debian .
hash debuild >/dev/null 2>&1 && debuild -us -uc || dpkg-buildpackage
cd ..

# Debianize and package the Viewer
cd kancolletool-viewer-${VERSION}/
cp -R ../../targets/debian/kancolletool-viewer/debian .
hash debuild >/dev/null 2>&1 && debuild -us -uc || dpkg-buildpackage
cd ..
