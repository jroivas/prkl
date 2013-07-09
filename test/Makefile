
test: test.o
	gcc -o $@ $^ -ldb

rebuild_test: test.c
	gcc -o $@ $^ -I.. -L.. -llmdb -lprkl

test.o: test.c

clean:
	rm -f *.o test

wrappertest: test
	LD_LIBRARY_PATH=.. ./test
