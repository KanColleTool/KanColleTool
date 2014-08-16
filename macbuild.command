#!/bin/bash
set -e

cmake .
make
macdeployqt tool/bin/KanColleTool.app
cpack -G DragNDrop
