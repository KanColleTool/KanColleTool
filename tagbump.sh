#!/bin/bash

VERSION=$(<VERSION)

git tag "v${VERSION}"
git submodule foreach "git tag v${VERSION}; git push --tags"
git push --tags

