.POSIX:
.SUFFIXES: .c .o
.PHONY: all lint clean

SDL_LDFLAGS = `sdl2-config  --libs`
SDL_CFLAGS = `sdl2-config --cflags`

CFLAGS = -Og -g
LINK = $(CC)
MARST = marst
M = \
win\

all: $M
.o:; $(LINK) $< $(SDL_LDFLAGS) $(LDFLAGS) -o $@
.c.o:; $(CC) $(SDL_CFLAGS) $(CFLAGS) $< -c
.c:
%: %.c

lint:; make CFLAGS='-Wall -Wextra -g -Og'
clean:; rm -f $M $(M:=.o)
