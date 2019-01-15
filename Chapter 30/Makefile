
BINARIES = main-two-cvs-while main-two-cvs-if main-one-cv-while main-two-cvs-while-extra-unlock
HEADERS = src/mythreads.h src/main-header.h src/main-common.c src/pc-header.h

all: $(BINARIES)

clean:
	rm -r bin
	mkdir bin

main-one-cv-while: src/main-one-cv-while.c $(HEADERS)
	gcc -o bin/main-one-cv-while src/main-one-cv-while.c -Wall -pthread

main-two-cvs-if: src/main-two-cvs-if.c $(HEADERS)
	gcc -o bin/main-two-cvs-if src/main-two-cvs-if.c -Wall -pthread

main-two-cvs-while: src/main-two-cvs-while.c $(HEADERS)
	gcc -o bin/main-two-cvs-while src/main-two-cvs-while.c -Wall -pthread

main-two-cvs-while-extra-unlock: src/main-two-cvs-while-extra-unlock.c $(HEADERS)
	gcc -o bin/main-two-cvs-while-extra-unlock src/main-two-cvs-while-extra-unlock.c -Wall -pthread


