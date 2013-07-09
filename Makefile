
CFLAGS=-fPIC -I../liblmdb/
OBJECTS=prkl_create.o prkl_error.o

all: prkl.so compability tests

mdblib:
	./scripts/build_mdb.sh

compability: libdb-5.1.so

prkl_create.o: prkl_create.c prkl_create.h prkl_types.h

prkl_error.o: prkl_error.c prkl_create.h prkl_types.h

prkl.so: $(OBJECTS)
	gcc -shared -Wl,-soname,libprkl.so.0 -Wl,--version-script symbols.ver -o libprkl.so.0.1 $^ -L../liblmdb -llmdb
	ln -sf libprkl.so.0.1 libprkl.so.0
	ln -sf libprkl.so.0 libprkl.so

libdb-5.1.so: $(OBJECTS)
	gcc -shared -Wl,-soname,libdb-5.1.so -Wl,--version-script symbols.ver -o libdb-5.1.so.0.1 $^ -L../liblmdb -llmdb
	ln -sf libdb-5.1.so.0.1 libdb-5.1.so.0
	ln -sf libdb-5.1.so.0 libdb-5.1.so

clean:
	rm -rf *.o libdb*.so* libprkl*.so* data.mdb lock.mdb
	@make -C test clean

tests: apitests abitests

apitests: prkl.so
	@make -C test run_api_test

abitests: compability
	@echo "*********************************"
	@echo "***** These tests will fail *****"
	@echo "*********************************"
	@make -C test run_abi_test || true
	@echo "*********************************"
