#!/bin/bash

VERSION=$(git describe --tags | grep -Po 'v\K([\w\.]+)')

# Remove old dist
rm -rf dist
mkdir -p dist/src

# Prepare tool sources
mkdir dist/src/kancolletool-${VERSION}
cp -R tool/*.{pro,cpp,h,ui,qrc,png} dist/src/kancolletool-${VERSION}/

# Prepare viewer sources
mkdir dist/src/kancolletool-viewer-${VERSION}
cp -R viewer/*.{pro,cpp,h,qrc,png,html,js} viewer/proxy-plugins/ dist/src/kancolletool-viewer-${VERSION}/

# Tarball it all up
cd dist/src
tar -czf kancolletool-${VERSION}.tar.gz kancolletool-${VERSION}
tar -czf kancolletool-viewer-${VERSION}.tar.gz kancolletool-viewer-${VERSION}
cd ../..
