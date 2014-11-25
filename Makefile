CFLAGS = -c -g -Wall -std=gnu99
GL_INCLUDE = -I/usr/include/GL
GL_LIBDIR = -L. -L/usr/X11R6/lib
GL_LIBRARIES = -lglut -lGL -lm -lGLU # -lXmu -lXext -lXi -lX11
CC = gcc
OS = "unknown"

# Add objectiveC library for MacOSX.
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Apple")),)
 GL_INCLUDE    = -I/usr/X11R6/include
 GL_LIBRARIES += -lobjc
 BROWSER = dillo
 OS = "osx"
endif
# Nothing to be done for Linux :o)
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Linux")),)
 OS = "linux"
 BROWSER = mozilla
endif
#

job: delaunay #dox

delaunay:	vertex.o \
		delaunay.o

	$(CC) $(GL_LIBDIR) \
		vertex.o \
		delaunay.o \
	$(GL_LIBRARIES) -o $@

clean:
	@echo "operating system = $(OS)"
	rm -rf *.o delaunay DOX

################################################################################
# Generate doxygen documentation of file two.c using command file two.dox.
#dox: two.c two.h
#	rm -rf DOX
#	doxygen two.dox
#

