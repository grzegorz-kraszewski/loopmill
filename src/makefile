###########################################
# LoopMill - tracker style MIDI sequencer #
# Grzegorz Kraszewski, 2016               #
###########################################

CC = gcc
CFLAGS = -nostartfiles -nostdlib -fomit-frame-pointer -fbaserel -O2 -D__NOLIBBASE__ -DUSE_INLINE_STDARG
OBJS = start.o main.o
EXE = LoopMill

all: $(OBJS)
	@Echo "Linking $(EXE)..."
	@$(CC) $(CFLAGS) -o $(EXE) $^

clean:
	rm -f *.o $(EXE)

start.o: start.c
	@Echo "Compiling $@..."
	@$(CC) $(CFLAGS) -fwritable-strings -c -o $@ $<

%.o: %.c
	@Echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

# dependencies

main.o: main.c main.h
start.o: start.c main.h
