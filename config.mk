# st version
VERSION = 0.8.1

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# includes and libs
INCS = -I$(X11INC) \
			 -I /usr/include \
       `pkg-config --cflags fontconfig` \
       `pkg-config --cflags freetype2`

ifeq ($(shell uname),OpenBSD)
OS = OpenBSD
CPPFLAGS = -DVERSION=\"$(VERSION)\" -D_XOPEN_SOURCE=600 -D_BSD_SOURCE
LIBS = -L$(X11LIB) -lm -lX11 -lutil -lXft \
       `pkg-config --libs fontconfig` \
       `pkg-config --libs freetype2`
else
OS = Linux
CPPFLAGS = -DVERSION=\"$(VERSION)\" -D_XOPEN_SOURCE=600
LIBS = -L/usr/lib -lc -L${X11LIB} -lm -lrt -lX11 -lutil -lXft -lXrender\
       `pkg-config --libs fontconfig` \
       `pkg-config --libs freetype2`
endif

# flags
STCFLAGS = $(INCS) $(CPPFLAGS) $(CFLAGS)
STLDFLAGS = $(LIBS) $(LDFLAGS)

# compiler and linker
# CC = c99

