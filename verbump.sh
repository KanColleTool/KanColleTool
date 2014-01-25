#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: verbump.sh X.X.X"
	exit
fi

echo $1 > VERSION

sed -i '' -e 's/#define KCT_VERSION .*/#define KCT_VERSION "'$1'"/' {tool,viewer}/version.h
sed -i '' -e 's/#define MyAppVersion .*/#define MyAppVersion "'$1'"/' targets/windows/KanColleTool.iss
sed -i '' -e 's/VERSION = .*/VERSION = '$1'/' {tool,viewer}/*.pro
sed -n -i '' -e '/CFBundleShortVersionString/{p;n;s/>.*</>'$1'</;};p' macviewer/KCTViewer/KCTViewer/KCTViewer-Info.plist

