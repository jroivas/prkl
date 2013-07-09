
all: abi_test api_test

abi_test: test.o
	gcc -o $@ $^ -ldb

api_test: test.c
	gcc -o $@ $^ -I.. -L.. -llmdb -lprkl

test.o: test.c

clean:
	rm -f *.o test api_test abi_test data.mdb lock.mdb

run_api_test: api_test
	LD_LIBRARY_PATH=.. ./api_test

run_abi_test: abi_test
	LD_LIBRARY_PATH=.. ./abi_test

