all: read
read: main.cpp libjson.so
	g++ -o $@ $< -Ijson -Wl,-rpath -Wl,. -L. -ljson
libjson.so: libjson/libjson.so
	ln -sf libjson/libjson.so .
clean:
	rm -f *.so *.o read
