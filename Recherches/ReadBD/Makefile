all: read
DEBUG=
LIB=
debug: DEBUG=-ggdb
debug: LIB=-dbg
debug: all
read: main.cpp libjson.so libjson-dbg.so
	g++ $(DEBUG) -o $@ $< -Ijson -Wl,-rpath -Wl,. -L. -ljson$(LIB)
libjson.so: libjson/libjson.so
	ln -sf libjson/libjson.so .
libjson-dbg.so: libjson/libjson-dbg.so
	ln -sf libjson/libjson-dbg.so .
clean:
	rm -f *.so *.o read
