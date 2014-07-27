#!/bin/bash
set -e

VERSION=$(<VERSION)

./build_source_tgz.sh

[[ -d dist/debian ]] && rm -rf dist/debian
mkdir -p dist/debian && cd dist/debian
cp ../kancolletool-$VERSION.tar.gz kancolletool_$VERSION.orig.tar.gz
tar -xzf kancolletool_$VERSION.orig.tar.gz
cd kancolletool-$VERSION

cp -R ../../../targets/debian/* .
debuild -S
