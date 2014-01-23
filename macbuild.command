#!/bin/bash
export PATH=$HOME/Qt/5.2.0/clang_64/bin:$PATH

# cd to the script's directory
cd "$( dirname "${BASH_SOURCE[0]}" )"

# Remove old dists
rm -rf dist
mkdir dist
mkdir dist/KanColleTool

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
cd macviewer/KCTViewer
rm -r build
xcodebuild -target KCTViewer -configuration Release
cp -R build/Release/KCTViewer.app ../../dist/KanColleTool/
rm -rf build
cd ../..

# Make a DMG of it all
hdiutil create "tmp.dmg" -ov -volname "KanColleTool" -fs "HFS+" -srcfolder dist/KanColleTool
hdiutil convert "tmp.dmg" -format "UDZO" -o "dist/KanColleTool.dmg"
rm -f tmp.dmg
