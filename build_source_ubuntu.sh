#!/bin/bash
set -e

VERSION=$(<VERSION)

./build_source_debian.sh --no-debuild

mkdir -p dist/ubuntu && cd dist/ubuntu

cp -R ../debian/* .
cd kancolletool-$VERSION

# Patch Debian's 'unstable' out for an Ubuntu codename and build
sed -i 's/) unstable;/) trusty;/' debian/changelog
debuild -S
