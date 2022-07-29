CXX		:= g++
CXX_FLAGS	:= -std=c++20 -O3

SCFLAGS		:= $(shell pkg-config --cflags fmt jsoncpp) -fconcepts
CCFLAGS		:= $(shell pkg-config --cflags sdl2 SDL2_mixer SDL2_image fmt jsoncpp) -fconcepts
WARNINGS	:= 

BIN		:= bin
SRC		:= src
INCLUDE		:= include
LIB		:= lib

SLIBS		:= $(shell pkg-config --libs fmt jsoncpp) -pthread
CLIBS		:= $(shell pkg-config --libs sdl2 SDL2_mixer SDL2_image fmt jsoncpp) -pthread -latomic
EXE_S		:= server
EXE_C		:= client

PKGS		:= $(shell command -v apt-get && echo install build-essential libsdl2-2.0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-dev libjsoncpp-dev || command -v pacman && echo -S sdl2 sdl2_image sdl2_mixer jsoncpp)

all: $(BIN)/$(EXE_S) $(BIN)/$(EXE_C)

$(BIN)/$(EXE_S): $(SRC)/*.cpp $(SRC)/main/main_server.cpp $(SRC)/model/*.cpp $(SRC)/model/mario/*.cpp $(SRC)/model/stage/*.cpp $(SRC)/utils/dataTransfer.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $(WARNINGS) $^ -o $@ $(SLIBS) $(SCFLAGS)
 
$(BIN)/$(EXE_C): $(SRC)/*.cpp $(SRC)/main/main_client.cpp $(SRC)/view/*.cpp $(SRC)/controller/*.cpp $(SRC)/utils/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $(WARNINGS) $^ -o $@ $(CLIBS) $(CCFLAGS)

deps:
	$(PKGS)

format:
	xargs clang-format -i < .clang-files

update-format:
	find src -name "*.[ch]pp" >.clang-files

touch:
	touch -c $(BIN)/$(EXE_S) $(BIN)/$(EXE_C)

clean:
	-rm $(BIN)/*
