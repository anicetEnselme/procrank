all: procbox.o libprocbox.so 

procbox.o: procbox.c
	gcc -c -fPIC procbox.c -o procbox.o

libprocbox.so: procbox.o
	gcc -shared procbox.o -o libprocbox.so
clean:
	rm *.o
	rm *.so
