CC		:=gcc
CFLAGS	:=-Wall -O3 -march=native -I. -std=c99 -D_POSIX_C_SOURCE=199309L -c
LDFLAGS	:=-O3 -lpthread

all: ../bin/bysleep ../bin/bytimecheck ../bin/gettimeMeter

../bin/bysleep: bysleep.o
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@
	
../bin/bytimecheck: bytimecheck.o
	$(CC) $(LDFLAGS) $^ -o $@	

../bin/gettimeMeter: gettimeMeter.o
	$(CC) $(LDFLAGS) $^ -o $@	

%.o: %.c common.c
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	rm -rf *.o