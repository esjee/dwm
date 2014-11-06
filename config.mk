VERSION = 6.0
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/include/X11
X11LIB = /usr/lib

# Xinerama
XINERAMALIBS = -L${X11LIB} -lXinerama
XINERAMAFLAGS = -DXINERAMA

# Pango XFT
PANGOINC = -pthread -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/freetype2
PANGOLIB = -lpangoxft-1.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfreetype -lfontconfig -lXft

# mpdclient
MPDCLIENTLIB = -lmpdclient

# includes and libs
INCS = -I.  -I${X11INC} ${PANGOINC}
LIBS =  -lc -L${X11LIB} -lX11 ${XINERAMALIBS} ${PANGOLIB} ${MPDCLIENTLIB}

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
CFLAGS += -O2 -std=c99 -pedantic -Wall -Wno-deprecated-declarations ${INCS} ${CPPFLAGS}
LDFLAGS += ${LIBS}

# debug flags
#CFLAGS = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
#LDFLAGS = -g ${LIBS}

# compiler and linker
CC = cc
