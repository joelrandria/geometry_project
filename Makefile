CFLAGS = -c -g -Wall -std=gnu99
CC = gcc
OS = "unknown"

# Add objectiveC library for MacOSX.
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Apple")),)
 GL_INCLUDE    = -I/usr/X11R6/include
 GL_LIBRARIES = -framework OpenGL -framework GLUT
 BROWSER = dillo
 OS = "__APPLE__"
endif
# Nothing to be done for Linux :o)
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Linux")),)
 OS = "__LINUX__"
 GL_INCLUDE = -I/usr/include/GL
 GL_LIBDIR = -L. -L/usr/X11R6/lib
 GL_LIBRARIES = -lglut -lGL -lm -lGLU # -lXmu -lXext -lXi -lX11
 BROWSER = mozilla
endif
#

job: delaunay #dox

delaunay:	settings.o \
		vertex.o \
		delaunay.o \
                construction.o \
		triangle.o \
                pqueue.o \
		tstack.o

	$(CC) $(GL_INCLUDE) $(GL_LIBDIR) \
		settings.o \
		vertex.o \
		delaunay.o \
                construction.o \
		triangle.o \
                pqueue.o \
		tstack.o \
	$(GL_LIBRARIES) -D$(OS) -o $@

delaunay.o:	delaunay.c

		$(CC) $(GL_INCLUDE) $(CFLAGS) -D$(OS) $<

dox:
	rm -rf doc
	doxygen

clean:

	@echo "operating system = $(OS), $(GL_INCLUDE) $(GL_LIBDIR)	"
	rm -rf *.o delaunay doc

