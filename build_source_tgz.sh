#!/bin/bash
set -e

VERSION=$(<VERSION)

mkdir -p dist/kancolletool-$VERSION && cd dist/kancolletool-$VERSION

git clone --recursive ../../viewer
git clone --recursive ../../tool
cp ../../CMakeLists.txt .

cd ..
tar --exclude-vcs -zcf kancolletool-$VERSION.tar.gz kancolletool-$VERSION
rm -rf kancolletool-$VERSION
