#!/bin/bash

VERSION=$(<VERSION)

# Set up a directory structure for the debian build
cd dist
rm -rf debian > /dev/null
mkdir debian

cd debian
mkdir kancolletool-${VERSION}
cp -R ../../tool/*.{pro,pri} kancolletool-${VERSION}
mkdir kancolletool-${VERSION}/src
cp -R ../../tool/src/*.{cpp,h,pro} kancolletool-${VERSION}/src
mkdir kancolletool-${VERSION}/resources
cp -R ../../tool/resources/*.{qrc,png,ico,desktop} kancolletool-${VERSION}/resources
mkdir kancolletool-${VERSION}/forms
cp -R ../../tool/forms/*.ui kancolletool-${VERSION}/forms

mkdir kancolletool-viewer-${VERSION}
cp -a ../../viewer/*.{pro,cpp,h,ui,qrc,png,ico,html,desktop} kancolletool-viewer-${VERSION}/

# Debianize and package the Tool
# Note that we're not signing these packages, simply because signing raises
# annoying errors on every machines except the one my keys are on
cd kancolletool-${VERSION}/
qmake
cp -a ../../../targets/debian/kancolletool/debian .
dh_make -s --createorig -y
hash debuild >/dev/null 2>&1 && debuild -i -us -uc || dpkg-buildpackage -d -us -uc
cd ..

# Debianize and package the Viewer
# See above about the explicit lack of signing
cd kancolletool-viewer-${VERSION}/
qmake
cp -a ../../../targets/debian/kancolletool-viewer/debian .
dh_make -s --createorig -y
hash debuild >/dev/null 2>&1 && debuild -i -us -uc || dpkg-buildpackage -d -us -uc
cd ..

# Go back to the root folder
cd ..
