#!/bin/bash
set -e

cmake .
make
macdeployqt tool/bin/KanColleTool.app
macdeployqt viewer/bin/KCTViewer.app
cpack -G DragNDrop
