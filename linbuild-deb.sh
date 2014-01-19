#!/bin/bash

# This both puts the sources in the right place and gives us $VERSION
source linbuild.sh

# Debianize and package the Tool
cd dist
cp kancolletool-${VERSION}.tar.gz kancolletool_${VERSION}.orig.tar.gz

cd kancolletool-${VERSION}/
cp -R ../../targets/debian/kancolletool/debian .
dpkg-buildpackage
