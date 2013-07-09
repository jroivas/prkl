
CFLAGS=-fPIC -I../liblmdb/
OBJECTS=prkl_create.o prkl_error.o

all: libprkl.so compability tests

help:
	@echo "Usage:"
	@echo "    make all        - Build all libs, tests and run tests"
	@echo "    make mdblib     - Build MDB library"
	@echo "    make libprkl.so - Build only libprkl.so"
	@echo "    make clean      - Clean build results"
	@echo "    make clean_all  - Clean everything"
	@echo "    make tests      - Build and run tests"

mdblib:
	./scripts/build_mdb.sh

compability: libdb-5.1.so

prkl_create.o: prkl_create.c prkl_create.h prkl_types.h

prkl_error.o: prkl_error.c prkl_create.h prkl_types.h

libprkl.so: $(OBJECTS)
	gcc -shared -Wl,-soname,libprkl.so.0 -Wl,--version-script symbols.ver -o libprkl.so.0.1 $^ -L../liblmdb -llmdb
	ln -sf libprkl.so.0.1 libprkl.so.0
	ln -sf libprkl.so.0 libprkl.so

libdb-5.1.so: libprkl.so
	ln -sf libprkl.so.0.1 libdb-5.1.so.0.1
	ln -sf libprkl.so.0.1 libdb-5.1.so.0
	ln -sf libprkl.so.0.1 libdb-5.1.so

clean:
	rm -rf *.o libdb*.so* libprkl*.so* data.mdb lock.mdb
	@make -C test clean

clean_all: clean
	rm -f liblmdb
	rm -f *.so*
	rm -rf mdb

tests: mdblib apitests abitests

apitests: libprkl.so
	@make -C test run_api_test

abitests: compability
	@echo "*********************************"
	@echo "***** These tests will fail *****"
	@echo "*********************************"
	@make -C test run_abi_test || true
	@echo "*********************************"
