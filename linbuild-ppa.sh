#!/bin/bash

# This gives us $VERSION and dist/src
source linbuild.sh

# Set up a directory structure for the ppa build
# (copypaste from linbuild-deb.sh)
cd dist
mkdir ppa
cp src/kancolletool-${VERSION}.tar.gz ppa/kancolletool_${VERSION}.orig.tar.gz
cp src/kancolletool-viewer-${VERSION}.tar.gz ppa/kancolletool-viewer_${VERSION}.orig.tar.gz

cd ppa
tar -xf kancolletool_${VERSION}.orig.tar.gz
tar -xf kancolletool-viewer_${VERSION}.orig.tar.gz

cp -R ../../targets/debian/kancolletool/debian kancolletool-${VERSION}/
cp -R ../../targets/debian/kancolletool-viewer/debian kancolletool-viewer-${VERSION}/

# Patch the changelogs to swap 'unstable' out for 'saucy'
# Without this, Launchpad will reject any attempt to push it
sed -i 's/) unstable; /) saucy; /' kancolletool{,-viewer}-${VERSION}/debian/changelog

# And patch in qt5-default as a build dep, otherwise Launchpad will fail to
# build the package; "qmake: could not find a Qt installation of ''"
sed -i 's/Build-Depends: /Build-Depends: qt5-default, /' kancolletool{,-viewer}-${VERSION}/debian/control

# Make a source package (-S) of the Tool
# The extra qmake call is to work around an annoying thing where the build
# fails if you're using one OS to build and another to sign, such as in my case
# where I'm building in a Debian VM and signing from my Arch installation.
cd kancolletool-${VERSION}
qmake
hash debuild >/dev/null 2>&1 && debuild -S || dpkg-buildpackage -S
cd ..

# Make a source package (-S) of the Viewer
# See above about the extra qmake call
cd kancolletool-viewer-${VERSION}
qmake
hash debuild >/dev/null 2>&1 && debuild -S || dpkg-buildpackage -S
cd ..

# Go back
cd ../..
