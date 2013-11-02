#!/bin/sh
GIT="/usr/bin/git"

CBRANCH="$(git rev-parse --abbrev-ref HEAD)"
#OUT="99-$(echo "$CBRANCH").patch"
OUT="99-esjee.patch"

"$GIT" diff master "$CBRANCH" >"$OUT"
