#!/bin/sh
WHITELIST="config.def.h config.mk dwm.1 dwm.c LICENSE Makefile README mpdcontrol.c"
CBRANCH="$(git rev-parse --abbrev-ref HEAD)"
#OUT="99-$(echo "$CBRANCH").patch"
OUT="99-esjee.patch"

make clean >/dev/null
git diff master $CBRANCH -- $WHITELIST >"$OUT"
