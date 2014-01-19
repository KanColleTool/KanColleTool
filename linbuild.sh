#!/bin/bash

VERSION=$(git describe --tags | grep -Po 'v\K([\w\.]+)')

# Remove old dist
rm -rf dist 2>/dev/null
mkdir dist

# Prepare tool sources
mkdir dist/kancolletool-${VERSION}
cp -R tool/*.{pro,c,cpp,h,ui,qrc,png} dist/kancolletool-${VERSION}/ 2>/dev/null

# Prepare viewer sources
mkdir dist/kancolletool-viewer-${VERSION}
cp -R viewer/*.{pro,c,cpp,h,ui,qrc,png} dist/kancolletool-viewer-${VERSION}/ 2>/dev/null

# Tarball it all up
cd dist
tar -czf kancolletool-${VERSION}.tar.gz kancolletool-${VERSION}
tar -czf kancolletool-viewer-${VERSION}.tar.gz kancolletool-viewer-${VERSION}
cd ..
