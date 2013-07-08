
CFLAGS=-fPIC

all: prkl.so

prkl.so: prkl_create.o
	gcc -shared -Wl,-soname,prkl.so.0 -o prkl.so.0.1 $^ 
	ln -sf prkl.so.0.1 prkl.so.0
	ln -sf prkl.so.0 prkl.so

clean:
	rm -rf *.o *.so*
