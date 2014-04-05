#!/bin/bash

VERSION=$(<VERSION)

# Remove old dist
rm -rf dist/src > /dev/null
mkdir -p dist/src

# Prepare tool sources
mkdir dist/src/kancolletool-${VERSION}
cp -R tool/*{.pro,pri,rc} dist/src/kancolletool-${VERSION}/
cp -R tool/src/*.{cpp,h,pro} dist/src/kancolletool-${VERSION}/
cp -R tool/resources/*.{qrc,png,desktop} dist/src/kancolletool-${VERSION}/
cp -R tool/forms/*.ui dist/src/kancolletool-${VERSION}/


# Prepare viewer sources
mkdir dist/src/kancolletool-viewer-${VERSION}
cp -R viewer/*.{pro,cpp,h,qrc,png,html} dist/src/kancolletool-viewer-${VERSION}/

# Tarball it all up
cd dist/src
tar -czf kancolletool-${VERSION}.tar.gz kancolletool-${VERSION}
tar -czf kancolletool-viewer-${VERSION}.tar.gz kancolletool-viewer-${VERSION}
cd ../..
