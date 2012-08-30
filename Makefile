WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS =  -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG =  $(INC)
CFLAGS_DEBUG =  $(CFLAGS) -Wswitch-default -std=c++0x -g
RESINC_DEBUG =  $(RESINC)
RCFLAGS_DEBUG =  $(RCFLAGS)
LIBDIR_DEBUG =  $(LIBDIR)
LIB_DEBUG = $(LIB) -llua -lgloox -lpthread
LDFLAGS_DEBUG =  $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/dramaqueen

INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O2 -std=c++0x
RESINC_RELEASE =  $(RESINC)
RCFLAGS_RELEASE =  $(RCFLAGS)
LIBDIR_RELEASE =  $(LIBDIR)
LIB_RELEASE = $(LIB) -llua -lgloox -lpthread
LDFLAGS_RELEASE =  $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/dramaqueen

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/server/ServerForge.o $(OBJDIR_DEBUG)/src/server/BaseServer.o $(OBJDIR_DEBUG)/src/news/daemon/DaemonForge.o $(OBJDIR_DEBUG)/src/news/daemon/Daemon.o $(OBJDIR_DEBUG)/src/news/client/BaseClient.o $(OBJDIR_DEBUG)/src/Helper.o $(OBJDIR_DEBUG)/src/news/bot/Bot.o $(OBJDIR_DEBUG)/src/news/NewsForge.o $(OBJDIR_DEBUG)/src/main.o $(OBJDIR_DEBUG)/src/logger/Logger.o $(OBJDIR_DEBUG)/src/config/Config.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/server/ServerForge.o $(OBJDIR_RELEASE)/src/server/BaseServer.o $(OBJDIR_RELEASE)/src/news/daemon/DaemonForge.o $(OBJDIR_RELEASE)/src/news/daemon/Daemon.o $(OBJDIR_RELEASE)/src/news/client/BaseClient.o $(OBJDIR_RELEASE)/src/Helper.o $(OBJDIR_RELEASE)/src/news/bot/Bot.o $(OBJDIR_RELEASE)/src/news/NewsForge.o $(OBJDIR_RELEASE)/src/main.o $(OBJDIR_RELEASE)/src/logger/Logger.o $(OBJDIR_RELEASE)/src/config/Config.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/src/server || mkdir -p $(OBJDIR_DEBUG)/src/server
	test -d $(OBJDIR_DEBUG)/src/news/daemon || mkdir -p $(OBJDIR_DEBUG)/src/news/daemon
	test -d $(OBJDIR_DEBUG)/src/news/client || mkdir -p $(OBJDIR_DEBUG)/src/news/client
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src
	test -d $(OBJDIR_DEBUG)/src/news/bot || mkdir -p $(OBJDIR_DEBUG)/src/news/bot
	test -d $(OBJDIR_DEBUG)/src/news || mkdir -p $(OBJDIR_DEBUG)/src/news
	test -d $(OBJDIR_DEBUG)/src/logger || mkdir -p $(OBJDIR_DEBUG)/src/logger
	test -d $(OBJDIR_DEBUG)/src/config || mkdir -p $(OBJDIR_DEBUG)/src/config

after_debug: 

debug: before_debug out_debug after_debug

out_debug: $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LDFLAGS_DEBUG) $(LIBDIR_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG) -o $(OUT_DEBUG)

$(OBJDIR_DEBUG)/src/server/ServerForge.o: src/server/ServerForge.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/server/ServerForge.cpp -o $(OBJDIR_DEBUG)/src/server/ServerForge.o

$(OBJDIR_DEBUG)/src/server/BaseServer.o: src/server/BaseServer.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/server/BaseServer.cpp -o $(OBJDIR_DEBUG)/src/server/BaseServer.o

$(OBJDIR_DEBUG)/src/news/daemon/DaemonForge.o: src/news/daemon/DaemonForge.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/news/daemon/DaemonForge.cpp -o $(OBJDIR_DEBUG)/src/news/daemon/DaemonForge.o

$(OBJDIR_DEBUG)/src/news/daemon/Daemon.o: src/news/daemon/Daemon.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/news/daemon/Daemon.cpp -o $(OBJDIR_DEBUG)/src/news/daemon/Daemon.o

$(OBJDIR_DEBUG)/src/news/client/BaseClient.o: src/news/client/BaseClient.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/news/client/BaseClient.cpp -o $(OBJDIR_DEBUG)/src/news/client/BaseClient.o

$(OBJDIR_DEBUG)/src/Helper.o: src/Helper.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/Helper.cpp -o $(OBJDIR_DEBUG)/src/Helper.o

$(OBJDIR_DEBUG)/src/news/bot/Bot.o: src/news/bot/Bot.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/news/bot/Bot.cpp -o $(OBJDIR_DEBUG)/src/news/bot/Bot.o

$(OBJDIR_DEBUG)/src/news/NewsForge.o: src/news/NewsForge.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/news/NewsForge.cpp -o $(OBJDIR_DEBUG)/src/news/NewsForge.o

$(OBJDIR_DEBUG)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/main.cpp -o $(OBJDIR_DEBUG)/src/main.o

$(OBJDIR_DEBUG)/src/logger/Logger.o: src/logger/Logger.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/logger/Logger.cpp -o $(OBJDIR_DEBUG)/src/logger/Logger.o

$(OBJDIR_DEBUG)/src/config/Config.o: src/config/Config.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/config/Config.cpp -o $(OBJDIR_DEBUG)/src/config/Config.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src/server
	rm -rf $(OBJDIR_DEBUG)/src/news/daemon
	rm -rf $(OBJDIR_DEBUG)/src/news/client
	rm -rf $(OBJDIR_DEBUG)/src
	rm -rf $(OBJDIR_DEBUG)/src/news/bot
	rm -rf $(OBJDIR_DEBUG)/src/news
	rm -rf $(OBJDIR_DEBUG)/src/logger
	rm -rf $(OBJDIR_DEBUG)/src/config

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE)/src/server || mkdir -p $(OBJDIR_RELEASE)/src/server
	test -d $(OBJDIR_RELEASE)/src/news/daemon || mkdir -p $(OBJDIR_RELEASE)/src/news/daemon
	test -d $(OBJDIR_RELEASE)/src/news/client || mkdir -p $(OBJDIR_RELEASE)/src/news/client
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src
	test -d $(OBJDIR_RELEASE)/src/news/bot || mkdir -p $(OBJDIR_RELEASE)/src/news/bot
	test -d $(OBJDIR_RELEASE)/src/news || mkdir -p $(OBJDIR_RELEASE)/src/news
	test -d $(OBJDIR_RELEASE)/src/logger || mkdir -p $(OBJDIR_RELEASE)/src/logger
	test -d $(OBJDIR_RELEASE)/src/config || mkdir -p $(OBJDIR_RELEASE)/src/config

after_release: 

release: before_release out_release after_release

out_release: $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LDFLAGS_RELEASE) $(LIBDIR_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE) -o $(OUT_RELEASE)

$(OBJDIR_RELEASE)/src/server/ServerForge.o: src/server/ServerForge.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/server/ServerForge.cpp -o $(OBJDIR_RELEASE)/src/server/ServerForge.o

$(OBJDIR_RELEASE)/src/server/BaseServer.o: src/server/BaseServer.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/server/BaseServer.cpp -o $(OBJDIR_RELEASE)/src/server/BaseServer.o

$(OBJDIR_RELEASE)/src/news/daemon/DaemonForge.o: src/news/daemon/DaemonForge.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/news/daemon/DaemonForge.cpp -o $(OBJDIR_RELEASE)/src/news/daemon/DaemonForge.o

$(OBJDIR_RELEASE)/src/news/daemon/Daemon.o: src/news/daemon/Daemon.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/news/daemon/Daemon.cpp -o $(OBJDIR_RELEASE)/src/news/daemon/Daemon.o

$(OBJDIR_RELEASE)/src/news/client/BaseClient.o: src/news/client/BaseClient.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/news/client/BaseClient.cpp -o $(OBJDIR_RELEASE)/src/news/client/BaseClient.o

$(OBJDIR_RELEASE)/src/Helper.o: src/Helper.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/Helper.cpp -o $(OBJDIR_RELEASE)/src/Helper.o

$(OBJDIR_RELEASE)/src/news/bot/Bot.o: src/news/bot/Bot.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/news/bot/Bot.cpp -o $(OBJDIR_RELEASE)/src/news/bot/Bot.o

$(OBJDIR_RELEASE)/src/news/NewsForge.o: src/news/NewsForge.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/news/NewsForge.cpp -o $(OBJDIR_RELEASE)/src/news/NewsForge.o

$(OBJDIR_RELEASE)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/main.cpp -o $(OBJDIR_RELEASE)/src/main.o

$(OBJDIR_RELEASE)/src/logger/Logger.o: src/logger/Logger.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/logger/Logger.cpp -o $(OBJDIR_RELEASE)/src/logger/Logger.o

$(OBJDIR_RELEASE)/src/config/Config.o: src/config/Config.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/config/Config.cpp -o $(OBJDIR_RELEASE)/src/config/Config.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)/src/server
	rm -rf $(OBJDIR_RELEASE)/src/news/daemon
	rm -rf $(OBJDIR_RELEASE)/src/news/client
	rm -rf $(OBJDIR_RELEASE)/src
	rm -rf $(OBJDIR_RELEASE)/src/news/bot
	rm -rf $(OBJDIR_RELEASE)/src/news
	rm -rf $(OBJDIR_RELEASE)/src/logger
	rm -rf $(OBJDIR_RELEASE)/src/config

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

