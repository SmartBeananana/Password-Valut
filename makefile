CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g -lm

test: src/HashTableImpl.c src/main.c
	$(CC) $(CFLAGS) src/HashTableImpl.c src/main.c -Iinclude -o bin/passwordVault

testHash: src/HashTableImpl.c src/testHashFunction.c
	$(CC) $(CFLAGS) src/HashTableImpl.c src/testHashFunction.c -Iinclude -o bin/hashFunction

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*
