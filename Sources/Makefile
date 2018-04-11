PROG=server client
all: $(PROG)
INCLUDE=-Iinclude/common/ -Iinclude/cjson/
LIBS=-Wl,-rpath -Wl,. -Llib/libcommon/ -Llib/libcjson/ -Llib/libjson/
DEBUG=
DBG=
ALL_O=
CLIENT_O=$(ALL_O) client.o
SERVER_O=$(ALL_O) server.o
debug: DEBUG=-ggdb -DDEBUG
debug: DBG=-dbg
debug: all
LINK=-lcommon$(DBG) -lcjson$(DBG) -ljson$(DBG)
SO=libcommon$(DBG).so libcjson$(DBG).so libjson$(DBG).so
CC=gcc $(DEBUG) -o $@ $(INCLUDE) -O2
libcommon.so: lib/libcommon/libcommon.so
	ln -sf $<
libcommon-dbg.so: lib/libcommon/libcommon-dbg.so
	ln -sf $<
libcjson.so: lib/libcjson/libcjson.so
	ln -sf $<
libcjson-dbg.so: lib/libcjson/libcjson-dbg.so
	ln -sf $<
libjson.so: lib/libjson/libjson.so
	ln -sf $<
libjson-dbg.so: lib/libjson/libjson-dbg.so
	ln -sf $<
%.o: %.c %.h
	$(CC) -c $<
client: $(CLIENT_O) $(SO)
	$(CC) $(CLIENT_O) $(LIBS) $(LINK)
server: $(SERVER_O) $(SO)
	$(CC) $(SERVER_O) $(LIBS) $(LINK)
.PHONY: clean
clean:
	rm -f *.so $(PROG)
	find -iname "*.o" -print -delete
