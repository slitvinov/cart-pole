.POSIX:
.SUFFIXES: .c .o
.PHONY: all lint clean

SDL_LDFLAGS = `sdl2-config  --libs`
SDL_CFLAGS = `sdl2-config --cflags`

M_LDFLAGS = -L../gfx -lgfx -lm
M_CFLAGS = -I../gfx

CFLAGS = -Og -g
LINK = $(CC)
M = \
circle\
win\
rectangle\
polygon\

all: $M
.o:; $(LINK) $< $(M_LDFLAGS) $(SDL_LDFLAGS) $(LDFLAGS) -o $@
.c.o:; $(CC) $(M_CFLAGS) $(SDL_CFLAGS) $(CFLAGS) $< -c
.c:
%: %.c

lint:; make CFLAGS='-Wall -Wextra -g -Og'
clean:; rm -f $M $(M:=.o)
