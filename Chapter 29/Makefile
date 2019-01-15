BINARIES = counter sloppy_counter list vector
HEADERS = counter.h sloppy_counter.h list.h

all: counter sloppy_counter list vector

clean:
	rm -f $(BINARIES)

counter:
	gcc -o counter src/counter.c -pthread

sloppy_counter:
	gcc -o sloppy_counter src/sloppy_counter.c -pthread

list:
	gcc -o list src/list.c -pthread

vector:
	gcc -o vector src/vector.c -pthread
