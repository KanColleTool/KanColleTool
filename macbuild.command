#!/bin/bash
set -e

cmake .
make
cpack -G DragNDrop
