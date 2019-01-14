CC = gcc
CFLAGS = -pthread -Wall -g
BINARIES = fork-join rendezvous barrier reader-writer reader-writer-nostarve mutex-nostarve
HEADERS = src/common_threads.h

%: src/%.c $(HEADERS)
	$(CC) -o bin/$@ $< $(CFLAGS)

.PHONY: all clean

all: $(BINARIES)

clean:
	rm -r bin
	mkdir bin
#fork-join: src/fork-join.c $(HEADERS)
#	$(CC) -o bin/fork-join src/fork-join.c $(CFLAGS)
