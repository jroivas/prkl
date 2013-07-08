
CFLAGS=-fPIC

all: prkl.so compability

prkl.so: prkl_create.o
	gcc -shared -Wl,-soname,prkl.so.0 -Wl,--version-script symbols.ver -o prkl.so.0.1 $^ 
	ln -sf prkl.so.0.1 prkl.so.0
	ln -sf prkl.so.0 prkl.so

clean:
	rm -rf *.o *.so*

compability: libdb-5.1.so

libdb-5.1.so: prkl_create.o
	gcc -shared -Wl,-soname,libdb-5.1.so -Wl,--version-script symbols.ver -o libdb-5.1.so.0.1 $^ 
	ln -sf libdb-5.1.so.0.1 libdb-5.1.so.0
	ln -sf libdb-5.1.so.0 libdb-5.1.so
