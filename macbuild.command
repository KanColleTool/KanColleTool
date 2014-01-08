#!/bin/bash
export PATH=$HOME/Qt/5.2.0/clang_64/bin:$PATH

# cd to the script's directory
cd "$( dirname "${BASH_SOURCE[0]}" )"

# Remove old dists
rm -rf dist
mkdir dist

# Build macviewer
cd macviewer/KCTViewer
rm -r build
xcodebuild -target KCTViewer -configuration Release
cp -R build/Release/KCTViewer.app ../../dist/
rm -rf build
cd ../..

# Build tool
cd tool
rm -rf KanColleTool.app
qmake
make
macdeployqt KanColleTool.app
cp -R KanColleTool.app ../dist/
make clean
rm -rf KanColleTool.app
cd ..

# Make a DMG of it all
hdiutil create "tmp.dmg" -ov -volname "KanColleTool" -fs "HFS+" -srcfolder dist
hdiutil convert "tmp.dmg" -format "UDZO" -o "KanColleTool.dmg"
rm -f tmp.dmg
