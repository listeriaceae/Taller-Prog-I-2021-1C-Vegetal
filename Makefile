CXX		:= g++
CXX_FLAGS	:= -std=c++20 -O3

LD_FLAGS_S	:= -fconcepts
LD_FLAGS_C	:= -fconcepts
WARNINGS	:= 
 
BIN		:= bin
SRC		:= src
INCLUDE		:= include
LIB		:= lib
 
LIBRARIES_S	:= -ljsoncpp -pthread
LIBRARIES_C	:= -lSDL2 -lSDL2_image -lSDL2_mixer -ljsoncpp -pthread
EXE_S		:= server
EXE_C		:= client
 
all: $(BIN)/$(EXE_S) $(BIN)/$(EXE_C)
 
$(BIN)/$(EXE_S): $(SRC)/*.cpp $(SRC)/main/main_server.cpp $(SRC)/model/*.cpp $(SRC)/model/mario/*.cpp $(SRC)/model/stage/*.cpp $(SRC)/model/collider/*.cpp $(SRC)/utils/dataTransfer.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $(WARNINGS) $^ -o $@ $(LIBRARIES_S) $(LD_FLAGS_S)
 
$(BIN)/$(EXE_C): $(SRC)/*.cpp $(SRC)/main/main_client.cpp $(SRC)/view/*.cpp $(SRC)/controller/*.cpp $(SRC)/utils/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $(WARNINGS) $^ -o $@ $(LIBRARIES_C) $(LD_FLAGS_C)

deps:
	sudo apt-get install build-essential gdb -y
	sudo apt-get install libsdl2-2.0 libsdl2-dev -y
	sudo apt-get install libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-dev -y
	sudo apt-get install libjsoncpp-dev -y

format:
	xargs clang-format -i < .clang-files

update-format:
	find src -name "*.[ch]pp" >.clang-files

touch:
	touch -c $(BIN)/$(EXE_S) $(BIN)/$(EXE_C)

clean:
	-rm $(BIN)/*
