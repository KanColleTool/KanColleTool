#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: verbump.sh X.X.X"
	exit
fi

echo $1 > VERSION

sed -i 's/#define KCT_VERSION .*/#define KCT_VERSION "'$1'"/' {tool,viewer}/version.h
sed -i 's/VERSION = .*/VERSION = '$1'/' {tool,viewer}/*.pro
sed -i '/<key>CFBundleShortVersionString<\/key>/!b;n;c\\t<string>'$1'</string>' macviewer/KCTViewer/KCTViewer/KCTViewer-Info.plist

