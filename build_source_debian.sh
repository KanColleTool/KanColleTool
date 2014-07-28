#!/bin/bash
set -e

NO_DEBUILD=false

for arg in "$@"; do
	case $arg in
		--no-debuild)
			NO_DEBUILD=true
	esac
done

VERSION=$(<VERSION)

[[ ! -f dist/kancolletool-$VERSION.tar.gz ]] && [[ ! -f dist/debian/kancolletool_$VERSION.orig.tar.gz ]] && ./build_source_tgz.sh

[[ -d dist/debian ]] && rm -rf dist/debian
mkdir -p dist/debian && cd dist/debian

cp ../kancolletool-$VERSION.tar.gz kancolletool_$VERSION.orig.tar.gz
tar -xzf kancolletool_$VERSION.orig.tar.gz
cd kancolletool-$VERSION

cp -R ../../../targets/debian/* .
$NO_DEBUILD || debuild -S
