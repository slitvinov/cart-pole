.POSIX:
.SUFFIXES: .c .o
.PHONY: lint clean

CFLAGS = -Og -g
SDL_CFLAGS = `sdl2-config --cflags`

L = libgfx.a
O = \
gfxPrimitives.o\

$L: $O; ar r $@ $O && ranlib $@
.c.o:; $(CC) $(CFLAGS) $(SDL_CFLAGS) $< -c

pole.o: pole.h

.c:
%: %.c

lint:; make CFLAGS='-Wall -Wextra -g -O2'
clean:; rm -f $L $O
