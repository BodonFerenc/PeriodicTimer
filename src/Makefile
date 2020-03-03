CC		:=gcc
CFLAGS	:=-Wall -O3 -march=native -I.
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