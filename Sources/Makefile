PROG=server client client-gui tests
all: $(PROG)
INCLUDE=-Iinclude/common/ -Iinclude/cjson/ `pkg-config --cflags gtk+-3.0` `pkg-config --cflags webkitgtk-3.0`
LIBS=-Wl,-rpath -Wl,. -Llib/libcommon/ -Llib/libcjson/ -Llib/libjson/ -lm
DEBUG=
DBG=
ALL_O=sys/RequestTypes.o  utils/JSONCheck.o utils/Date.o utils/Replace.o
ALL_CLIENT=sys/ClientRequest.o sys/ClientRequests.o utils/Connexion.o sys/ClientRunnerContinue.o utils/FileToString.o
CLIENT_O=$(ALL_O) $(ALL_CLIENT) client.o sys/ClientRunner.o utils/ReadInput.o sys/ClientRunner_MainMenu.o sys/ClientRunner_UserSession.o
SERVER_O=$(ALL_O) server.o sys/ServerRunner.o utils/BDD.o sys/ClientHandler.o  utils/Client.o sys/Requests.o sys/ServerRunner_startInfos.o utils/Distance.o
GUI_O=$(ALL_O) $(ALL_CLIENT) client-gui.o gui/GUIHandleWebKit.o utils/HTMLGenerator.o utils/Headers.o
GTK=`pkg-config --libs gtk+-3.0` `pkg-config --libs webkitgtk-3.0`
debug: DEBUG=-ggdb -DDEBUG
debug: DBG=-dbg
debug: libcommon-dbg.so libcjson-dbg.so libjson-dbg.so
debug: all
LINK=-lcommon$(DBG) -lcjson$(DBG) -ljson$(DBG) -pthread
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
	$(CC) $(CLIENT_O) $(LIBS) $(LINK) # -lncurses -lcdk
server: $(SERVER_O) $(SO)
	$(CC) $(SERVER_O) $(LIBS) $(LINK)
client-gui: $(GUI_O) $(SO)
	$(CC) $(GUI_O) $(LIBS) $(LINK) $(GTK)
.PHONY: clean tests
clean:
	rm -f *.so $(PROG)
	find -iname "*.o" -print -delete
	find -iname "*.bin" -print -delete
tests: test/TestReadInput.bin test/TestCard.bin test/TestUsersDistance.bin
test/TestReadInput.bin: utils/ReadInput.o utils/Date.o utils/JSONCheck.o
test/TestCard.bin: utils/Distance.o utils/BDD.o utils/Distance.o utils/Client.o utils/Replace.o
test/TestUsersDistance.bin: utils/BDD.o utils/Distance_utilisateur.o utils/Client.o utils/Replace.o
%.bin: %.c
	$(CC) $^ $(LIBS) $(LINK)

#Deps
utils/ReadInput.o: utils/Date.o
