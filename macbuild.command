#!/bin/bash
export PATH=$HOME/Qt/5.2.0/clang_64/bin:$PATH

# cd to the script's directory
cd "$( dirname "${BASH_SOURCE[0]}" )"

# Remove old dists
rm -rf dist
mkdir dist
mkdir dist/KanColleTool

# Update cocoapods
cd macviewer
pod install
if [ $? -ne 0 ]; then
	echo "$(tput setab 1)Error:$(tput sgr0) Cocoapods isn't installed"
	echo "Install it with:"
	echo "$(tput bold)gem install cocoapods$(tput sgr0)"
	exit
fi
cd ..

# Build tool
cd tool
rm -rf KanColleTool.app
qmake
make
macdeployqt KanColleTool.app
cp -R KanColleTool.app ../dist/KanColleTool/
make clean
rm -rf KanColleTool.app
cd ..

# Build macviewer
cd macviewer
rm -rf build
mkdir build
xcodebuild -workspace KCTViewer.xcworkspace -scheme KCTViewer -configuration Release -derivedDataPath ./build
cp -R build/Build/Products/Release/KCTViewer.app ../dist/KanColleTool/
rm -rf build
cd ..

# Make a DMG of it all
hdiutil create "/tmp/KanColleTool-macbuild-tmp.dmg" -ov -volname "KanColleTool" -fs "HFS+" -srcfolder dist/KanColleTool
hdiutil convert "/tmp/KanColleTool-macbuild-tmp.dmg" -format "UDZO" -o "dist/KanColleTool.dmg"
rm -f "/tmp/KanColleTool-macbuild-tmp.dmg"
