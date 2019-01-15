
ALL = vector-deadlock vector-global-order vector-try-wait vector-avoid-hold-and-wait vector-nolock
COMMON = src/vector-header.h src/main-common.c src/main-header.h

all: $(ALL)

clean:
	rm -r bin
	mkdir bin

vector-deadlock: src/vector-deadlock.c $(COMMON)
	gcc -o bin/vector-deadlock src/vector-deadlock.c -Wall -pthread -O

vector-global-order: src/vector-global-order.c $(COMMON)
	gcc -o bin/vector-global-order src/vector-global-order.c -Wall -pthread -O

vector-try-wait: src/vector-try-wait.c $(COMMON)
	gcc -o bin/vector-try-wait src/vector-try-wait.c -Wall -pthread -O

vector-avoid-hold-and-wait: src/vector-avoid-hold-and-wait.c $(COMMON)
	gcc -o bin/vector-avoid-hold-and-wait src/vector-avoid-hold-and-wait.c -Wall -pthread -O

vector-nolock: src/vector-nolock.c $(COMMON)
	gcc -o bin/vector-nolock src/vector-nolock.c -Wall -pthread -O

