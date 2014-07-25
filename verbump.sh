#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Usage: verbump.sh X X X"
	exit
fi

VERSION="${1}.${2}.${3}"

echo $VERSION > VERSION

sed -i '' -e "s/set\(VERSION_MAJOR .*\)/set\(VERSION_MAJOR $1\)/" {.,tool,viewer}/src/CMakeLists.txt
sed -i '' -e "s/set\(VERSION_MINOR .*\)/set\(VERSION_MINOR $2\)/" {.,tool,viewer}/src/CMakeLists.txt
sed -i '' -e "s/set\(VERSION_PATCH .*\)/set\(VERSION_PATCH $3\)/" {.,tool,viewer}/src/CMakeLists.txt
sed -i '' -e "s/#define MyAppVersion .*/#define MyAppVersion \"$VERSION\"/" targets/windows/KanColleTool.iss
sed -n -i '' -e '/CFBundleShortVersionString/{p;n;s/>.*</>'$VERSION'</;};p' macviewer/KCTViewer/KCTViewer-Info.plist
