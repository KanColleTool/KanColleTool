#!/bin/bash

VERSION=$(git describe --tags | grep -Po 'v\K([\w\.]+)')

# Remove old dist
rm -rf dist
mkdir dist

# Prepare tool sources
mkdir dist/kancolletool-${VERSION}
cp -R tool/*.{pro,cpp,h,ui,qrc,png} dist/kancolletool-${VERSION}/

# Prepare viewer sources
mkdir dist/kancolletool-viewer-${VERSION}
cp -R viewer/*.{pro,cpp,h,qrc,png,html,js} viewer/proxy-plugins/ dist/kancolletool-viewer-${VERSION}/

# Tarball it all up
cd dist
tar -czf kancolletool-${VERSION}.tar.gz kancolletool-${VERSION}
tar -czf kancolletool-viewer-${VERSION}.tar.gz kancolletool-viewer-${VERSION}
cd ..
