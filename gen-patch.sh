#!/bin/sh
GIT="/usr/bin/git"
OUT="99-esjee.patch"

"$GIT" diff master esjee >"$OUT"
