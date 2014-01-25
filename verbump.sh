#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Usage: verbump.sh X X X"
	exit
fi

VERSION="${1}.${2}.${3}"
VERSION_RC="${1}, ${2}, ${3}, 0"

echo $VERSION > VERSION

sed -i '' -e "s/#define KCT_VERSION .*/#define KCT_VERSION \"$VERSION\"/" {tool,viewer}/version.h
sed -i '' -e "s/#define MyAppVersion .*/#define MyAppVersion $VERSION/" targets/windows/KanColleTool.iss
sed -i '' -e "s/VERSION = .*/VERSION = $VERSION/" {tool,viewer}/*.pro
sed -n -i '' -e '/CFBundleShortVersionString/{p;n;s/>.*</>'$VERSION'</;};p' macviewer/KCTViewer/KCTViewer/KCTViewer-Info.plist
sed -i '' -e "s/\( *\)FILEVERSION\( *\).*/\1FILEVERSION\2${VERSION_RC}/" {tool,viewer}/*.rc
sed -i '' -e "s/\( *\)PRODUCTVERSION\( *\).*/\1PRODUCTVERSION\2${VERSION_RC}/" {tool,viewer}/*.rc
