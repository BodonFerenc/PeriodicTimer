CC		:=gcc
CFLAGS	:=-Wall -O3 -march=native -I. -std=c99 -D_POSIX_C_SOURCE=199309L
LDFLAGS	:=-O3 -lpthread

all: ../bin/bysleep ../bin/bytimecheck

../bin/bysleep: bysleep.o
	$(CC) $(LDFLAGS) $^ -o $@
	
../bin/bytimecheck: bytimecheck.o
	$(CC) $(LDFLAGS) $^ -o $@	

%o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o