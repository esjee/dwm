#!/bin/bash
CBRANCH="$(git rev-parse --abbrev-ref HEAD)"

for i in config.def.h config.mk dwm.1 dwm.c LICENSE Makefile README mpdcontrol.c
do
	OUT="99-esjee-${i}.patch"
	git diff master $CBRANCH -- ${i} >"$OUT"
done
make clean >/dev/null
