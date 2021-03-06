PROG=server client client-gui tests
all: $(PROG)
INCLUDE=-Iinclude/common/ -Iinclude/cjson/ `pkg-config --cflags gtk+-3.0` `pkg-config --cflags webkitgtk-3.0`
LIBS=-Wl,-rpath -Wl,. -Llib/libcommon/ -Llib/libcjson/ -Llib/libjson/ -lm
DEBUG=
DBG=
ALL_O=sys/RequestTypes.o  utils/JSONCheck.o utils/Date.o utils/Replace.o
ALL_CLIENT=sys/ClientRequest.o sys/ClientRequests.o utils/Connexion.o sys/ClientRunnerContinue.o utils/FileToString.o
CLIENT_O=$(ALL_O) $(ALL_CLIENT) client.o sys/ClientRunner.o utils/ReadInput.o sys/ClientRunner_MainMenu.o sys/ClientRunner_UserSession.o
SERVER_O=$(ALL_O) server.o sys/ServerRunner.o utils/BDD.o sys/ClientHandler.o  utils/Client.o sys/Requests.o sys/ServerRunner_startInfos.o utils/Distance.o utils/RandomReco.o utils/Distance_utilisateur.o utils/QuickSort.o utils/MergeSort.o
GUI_O=$(ALL_O) $(ALL_CLIENT) client-gui.o gui/GUIHandleWebKit.o utils/HTMLGenerator.o utils/Headers.o utils/HTMLGeneratorConnect.o gui/GUIMap.o utils/HTMLMenuBar.o utils/HTMLMenuContent.o utils/HTMLFicheFilm.o utils/HTMLFilm.o gui/Export.o utils/HTMLExport.o
GTK=`pkg-config --libs gtk+-3.0` `pkg-config --libs webkitgtk-3.0`
#G_DEBUG=fatal-warnings
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
.PHONY: clean tests release
clean:
	rm -f *.so $(PROG)
	find -iname "*.o" -print -delete
	find -iname "*.bin" -print -delete
tests: test/TestReadInput.bin test/TestCard.bin test/TestUsersDistance.bin
test/TestReadInput.bin: utils/ReadInput.o utils/Date.o utils/JSONCheck.o
test/TestCard.bin: utils/Distance.o utils/BDD.o utils/Distance.o utils/Client.o utils/Replace.o
test/TestUsersDistance.bin: utils/BDD.o utils/Distance_utilisateur.o utils/Client.o utils/Replace.o utils/MergeSort.o utils/QuickSort.o
%.bin: %.c
	$(CC) $^ $(LIBS) $(LINK)

#Deps
utils/ReadInput.o: utils/Date.o

release: clean client client-gui server
	rm -rf build
	mkdir -p build/client
	mkdir -p build/client-gui
	mkdir -p build/server
	mkdir -p build/server/data
	cp -rv server lib/*/*.so build/server/
	cp -rv data/users.json data/genres.json data/bd.json build/server/data/
	mkdir -p build/client/web/
	cp -rv client lib/*/*.so build/client
	cp -rv web/img build/client/web/
	cp -rv client-gui lib/*/*.so web build/client-gui/
	rm -rf build/client-gui/web/dev
	7z a build/all.7z build/client build/client-gui build/server
	7z a build/client.7z build/client
	7z a build/client-gui.7z build/client-gui
	7z a build/server.7z build/server
