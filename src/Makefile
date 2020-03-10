CC		:=gcc
CFLAGS	:=-Wall -O3 -march=native -I. -std=c99 -D_POSIX_C_SOURCE=199309L -c
LDFLAGS	:=-O3 -lpthread
BINDIR  :=../bin
OBJDIR  :=../obj

all: $(BINDIR)/bysleep $(BINDIR)/bytimecheckjumpforward $(BINDIR)/bytimecheckstrict $(BINDIR)/corefnsmeter

$(BINDIR)/%: $(OBJDIR)/%.o
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@


$(OBJDIR)/bytimecheckstrict.o: bytimecheck.c common.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -DsetNextTriggerTime=setNextTriggerTimeStrict -o $@ $<

$(OBJDIR)/bytimecheckjumpforward.o: bytimecheck.c common.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -DsetNextTriggerTime=setNextTriggerTimeJumpForward -o $@ $<

$(OBJDIR)/%.o: %.c common.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*.o