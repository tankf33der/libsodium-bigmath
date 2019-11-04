all:
	gcc -fPIC -c libsobig.c -o libsobig.o
	gcc -shared -Wl,-soname,libsobig.so.0 -o libsobig.so.0 libsobig.o -lc
	sudo cp -uf libsobig.so.0 /usr/local/lib
	sudo ldconfig
clean:
	rm -rf *.o *.0

