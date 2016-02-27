CC=gcc
CFLAGS=-O3 -msse2
LDFLAGS=-lm

stb_image: main.c stb_image.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
