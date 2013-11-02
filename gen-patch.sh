#!/bin/sh
GIT="/usr/bin/git"
WHITELIST="config.def.h config.mk dwm.1 dwm.c LICENSE Makefile README mpdcontrol.c"
CBRANCH="$(git rev-parse --abbrev-ref HEAD)"
#OUT="99-$(echo "$CBRANCH").patch"
OUT="99-esjee.patch"

$GIT diff master $CBRANCH -- $WHITELIST >"$OUT"
