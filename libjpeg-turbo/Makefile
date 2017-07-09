LIBJPEG-TURBO_VERSION=1.5.0

CC=gcc
CFLAGS=-O3 -msse2 -I./libjpeg-turbo-$(LIBJPEG-TURBO_VERSION)
LDFLAGS=

all: libjpeg-turbo

libjpeg-turbo: main.c libjpeg.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< libjpeg.a

libjpeg.a:
	curl -fL "https://github.com/libjpeg-turbo/libjpeg-turbo/archive/$(LIBJPEG-TURBO_VERSION).tar.gz" | tar -xz
	(cd libjpeg-turbo-$(LIBJPEG-TURBO_VERSION) && autoreconf -fiv)
	(mkdir -p build && cd build && ../libjpeg-turbo-$(LIBJPEG-TURBO_VERSION)/configure && make)
	cp build/jconfig.h libjpeg-turbo-$(LIBJPEG-TURBO_VERSION)/
	cp build/.libs/$@ ./

clean:
	rm -f libjpeg-turbo
	rm -f libjpeg.a
	rm -rf build
	rm -rf libjpeg-turbo-$(LIBJPEG-TURBO_VERSION)

.PHONY: all clean
