CXX		:= g++
CXX_FLAGS	:= -std=c++20 -O3 -flto=auto

SCFLAGS		:= $(shell pkg-config --cflags fmt jsoncpp) -fconcepts
CCFLAGS		:= $(shell pkg-config --cflags sdl2 SDL2_mixer SDL2_image fmt jsoncpp) -fconcepts
WARNINGS	:= 

BIN		:= bin
OBJ		:= obj
SRC		:= src

SLIBS		:= $(shell pkg-config --libs fmt jsoncpp) -pthread
CLIBS		:= $(shell pkg-config --libs sdl2 SDL2_mixer SDL2_image fmt jsoncpp) -pthread -latomic

PKGS		:= $(shell command -v apt-get && echo install build-essential libsdl2-2.0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-dev libjsoncpp-dev || command -v pacman && echo -S sdl2 sdl2_image sdl2_mixer jsoncpp)

OBJS	:= ${OBJ}/configuration.o ${OBJ}/logger.o ${OBJ}/dataTransfer.o
OBJSS	:= ${OBJ}/server/main.o ${OBJ}/server/Server.o ${OBJ}/server/tcp_server.o ${OBJ}/server/Barril.o ${OBJ}/server/EnemigoFuego.o ${OBJ}/server/Mario.o ${OBJ}/server/Nivel1.o ${OBJ}/server/Nivel2.o ${OBJ}/server/AireState.o ${OBJ}/server/GameOverState.o ${OBJ}/server/LevelCompletedState.o ${OBJ}/server/MarioState.o ${OBJ}/server/MuriendoState.o ${OBJ}/server/SueloState.o ${OBJ}/server/TrepandoState.o ${OBJ}/server/MovingPlatform.o ${OBJ}/server/Stage.o
OBJSC	:= ${OBJ}/client/main.o ${OBJ}/client/Client.o ${OBJ}/client/textureHandler.o ${OBJ}/client/AudioController.o ${OBJ}/client/MarioController.o ${OBJ}/client/BarrilVista.o ${OBJ}/client/DonkeyKongVista.o ${OBJ}/client/EnemigoFuegoVista.o ${OBJ}/client/FuegoVista.o ${OBJ}/client/HammerVista.o ${OBJ}/client/InterludeVista.o ${OBJ}/client/MarioVista.o ${OBJ}/client/Nivel1Vista.o ${OBJ}/client/Nivel2Vista.o ${OBJ}/client/NivelVista.o ${OBJ}/client/PaulineVista.o ${OBJ}/client/PlataformaMovilVista.o ${OBJ}/client/PoleaVista.o ${OBJ}/client/showMessage.o ${OBJ}/client/StartPageView.o ${OBJ}/client/StatsVista.o ${OBJ}/client/TextRenderer.o

all: ${BIN}/server ${BIN}/client

${BIN}/server: ${OBJS} ${OBJSS}
	mkdir -p bin
	${CXX} ${CXX_FLAGS} ${WARNINGS} $^ -o $@ ${SLIBS} ${SCFLAGS}
 
${BIN}/client: ${OBJS} ${OBJSC}
	mkdir -p bin
	${CXX} ${CXX_FLAGS} ${WARNINGS} $^ -o $@ ${CLIBS} ${CCFLAGS}

${OBJ}/configuration.o: ${SRC}/configuration.cpp ${SRC}/configuration.hpp ${SRC}/logger.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/logger.o: ${SRC}/logger.cpp ${SRC}/logger.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/dataTransfer.o: ${SRC}/utils/dataTransfer.cpp ${SRC}/utils/dataTransfer.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/main.o: ${SRC}/main/main_server.cpp ${SRC}/configuration.hpp ${SRC}/logger.hpp ${SRC}/model/Server.hpp ${SRC}/utils/tcp_server.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Server.o: ${SRC}/model/Server.cpp ${SRC}/model/Server.hpp ${SRC}/configuration.hpp ${SRC}/logger.hpp ${SRC}/model/Interlude.hpp ${SRC}/model/Nivel1.hpp ${SRC}/model/Nivel2.hpp ${SRC}/model/Mario.hpp ${SRC}/utils/Constants.hpp ${SRC}/utils/dataTransfer.hpp ${SRC}/utils/estadoJuego.hpp ${SRC}/utils/player.hpp ${SRC}/utils/tcp_server.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/tcp_server.o: ${SRC}/utils/tcp_server.cpp ${SRC}/utils/tcp_server.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Barril.o: ${SRC}/model/Barril.cpp ${SRC}/model/Barril.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/EnemigoFuego.o: ${SRC}/model/EnemigoFuego.cpp ${SRC}/model/EnemigoFuego.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Mario.o: ${SRC}/model/Mario.cpp ${SRC}/model/Mario.hpp ${SRC}/model/mario/SueloState.hpp ${SRC}/model/mario/MuriendoState.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Nivel1.o: ${SRC}/model/Nivel1.cpp ${SRC}/model/Nivel1.hpp ${SRC}/model/Entidad.hpp ${SRC}/configuration.hpp ${SRC}/logger.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Nivel2.o: ${SRC}/model/Nivel2.cpp ${SRC}/model/Nivel2.hpp ${SRC}/model/Entidad.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/AireState.o: ${SRC}/model/mario/AireState.cpp ${SRC}/model/mario/AireState.hpp ${SRC}/model/mario/SueloState.hpp ${SRC}/model/mario/MuriendoState.hpp ${SRC}/model/Mario.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/GameOverState.o: ${SRC}/model/mario/GameOverState.cpp ${SRC}/model/mario/GameOverState.hpp ${SRC}/model/Mario.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/LevelCompletedState.o: ${SRC}/model/mario/LevelCompletedState.cpp ${SRC}/model/mario/LevelCompletedState.hpp ${SRC}/model/Mario.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/MarioState.o: ${SRC}/model/mario/MarioState.cpp ${SRC}/model/mario/MarioState.hpp ${SRC}/model/mario/SueloState.hpp ${SRC}/model/Mario.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/MuriendoState.o: ${SRC}/model/mario/MuriendoState.cpp ${SRC}/model/mario/MuriendoState.hpp ${SRC}/model/mario/GameOverState.hpp ${SRC}/model/mario/SueloState.hpp ${SRC}/model/Mario.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/SueloState.o: ${SRC}/model/mario/SueloState.cpp ${SRC}/model/mario/SueloState.hpp ${SRC}/model/mario/AireState.hpp ${SRC}/model/mario/TrepandoState.hpp ${SRC}/model/Mario.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/TrepandoState.o: ${SRC}/model/mario/TrepandoState.cpp ${SRC}/model/mario/TrepandoState.hpp ${SRC}/model/mario/SueloState.hpp ${SRC}/model/mario/LevelCompletedState.hpp ${SRC}/model/Mario.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/MovingPlatform.o: ${SRC}/model/stage/MovingPlatform.cpp ${SRC}/model/stage/MovingPlatform.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Stage.o: ${SRC}/model/stage/Stage.cpp ${SRC}/model/stage/Stage.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/main.o: ${SRC}/main/main_client.cpp ${SRC}/configuration.hpp ${SRC}/logger.hpp ${SRC}/view/Client.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/Client.o: ${SRC}/view/Client.cpp ${SRC}/view/Client.hpp ${SRC}/view/Nivel1Vista.hpp ${SRC}/view/Nivel2Vista.hpp ${SRC}/view/InterludeVista.hpp ${SRC}/view/StartPageView.hpp ${SRC}/view/showMessage.hpp ${SRC}/configuration.hpp ${SRC}/logger.hpp ${SRC}/controller/AudioController.hpp ${SRC}/controller/MarioController.hpp ${SRC}/utils/Constants.hpp ${SRC}/utils/estadoJuego.hpp ${SRC}/utils/dataTransfer.hpp ${SRC}/utils/textureHandler.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/textureHandler.o: ${SRC}/utils/textureHandler.cpp ${SRC}/utils/textureHandler.hpp ${SRC}/logger.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/AudioController.o: ${SRC}/controller/AudioController.cpp ${SRC}/controller/AudioController.hpp ${SRC}/logger.hpp ${SRC}/utils/marioStructs.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/MarioController.o: ${SRC}/controller/MarioController.cpp ${SRC}/controller/MarioController.hpp ${SRC}/controller/AudioController.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/BarrilVista.o: ${SRC}/view/BarrilVista.cpp ${SRC}/view/BarrilVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/DonkeyKongVista.o: ${SRC}/view/DonkeyKongVista.cpp ${SRC}/view/DonkeyKongVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/EnemigoFuegoVista.o: ${SRC}/view/EnemigoFuegoVista.cpp ${SRC}/view/EnemigoFuegoVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/FuegoVista.o: ${SRC}/view/FuegoVista.cpp ${SRC}/view/FuegoVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/HammerVista.o: ${SRC}/view/HammerVista.cpp ${SRC}/view/HammerVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/InterludeVista.o: ${SRC}/view/InterludeVista.cpp ${SRC}/view/InterludeVista.hpp ${SRC}/view/TextRenderer.hpp ${SRC}/configuration.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/MarioVista.o: ${SRC}/view/MarioVista.cpp ${SRC}/view/MarioVista.hpp ${SRC}/view/HammerVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/Nivel1Vista.o: ${SRC}/view/Nivel1Vista.cpp ${SRC}/view/Nivel1Vista.hpp ${SRC}/view/PlataformaMovilVista.hpp ${SRC}/view/HammerVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/Nivel2Vista.o: ${SRC}/view/Nivel2Vista.cpp ${SRC}/view/Nivel2Vista.hpp ${SRC}/view/HammerVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/NivelVista.o: ${SRC}/view/NivelVista.cpp ${SRC}/view/NivelVista.hpp ${SRC}/configuration.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/PaulineVista.o: ${SRC}/view/PaulineVista.cpp ${SRC}/view/PaulineVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/PlataformaMovilVista.o: ${SRC}/view/PlataformaMovilVista.cpp ${SRC}/view/PlataformaMovilVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/PoleaVista.o: ${SRC}/view/PoleaVista.cpp ${SRC}/view/PoleaVista.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/showMessage.o: ${SRC}/view/showMessage.cpp ${SRC}/view/showMessage.hpp ${SRC}/view/TextRenderer.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/StartPageView.o: ${SRC}/view/StartPageView.cpp ${SRC}/view/StartPageView.hpp ${SRC}/view/TextRenderer.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/StatsVista.o: ${SRC}/view/StatsVista.cpp ${SRC}/view/StatsVista.hpp ${SRC}/view/TextRenderer.hpp ${SRC}/configuration.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/TextRenderer.o: ${SRC}/view/TextRenderer.cpp ${SRC}/view/TextRenderer.hpp ${SRC}/utils/Constants.hpp
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${SRC}/model/Server.hpp: ${SRC}/utils/player.hpp ${SRC}/utils/user.hpp
${SRC}/model/Barril.hpp: ${SRC}/utils/Constants.hpp ${SRC}/utils/dimensiones.hpp ${SRC}/utils/punto.hpp
${SRC}/model/EnemigoFuego.hpp: ${SRC}/utils/Constants.hpp ${SRC}/utils/dimensiones.hpp ${SRC}/utils/punto.hpp
${SRC}/model/Entidad.hpp: ${SRC}/utils/punto.hpp
${SRC}/model/Hammer.hpp: ${SRC}/utils/fixed_point.hpp ${SRC}/utils/punto.hpp ${SRC}/utils/dimensiones.hpp
${SRC}/model/Interlude.hpp: ${SRC}/model/Scene.hpp
${SRC}/model/Mario.hpp: ${SRC}/model/mario/MarioState.hpp ${SRC}/model/mario/AudioObserver.hpp ${SRC}/model/Entidad.hpp ${SRC}/model/Hammer.hpp ${SRC}/utils/marioStructs.hpp ${SRC}/utils/punto.hpp
${SRC}/model/Nivel1.hpp: ${SRC}/model/stage/MovingPlatform.hpp ${SRC}/model/EnemigoFuego.hpp ${SRC}/model/Nivel.hpp
${SRC}/model/Nivel2.hpp: ${SRC}/model/Barril.hpp ${SRC}/model/Nivel.hpp
${SRC}/model/Nivel.hpp: ${SRC}/model/Scene.hpp ${SRC}/model/stage/Stage.hpp ${SRC}/model/Mario.hpp ${SRC}/model/Hammer.hpp
${SRC}/model/Scene.hpp: ${SRC}/utils/estadoJuego.hpp
${SRC}/model/mario/AireState.hpp: ${SRC}/model/mario/MarioState.hpp
${SRC}/model/mario/GameOverState.hpp: ${SRC}/model/mario/MarioState.hpp
${SRC}/model/mario/LevelCompletedState.hpp: ${SRC}/model/mario/MarioState.hpp
${SRC}/model/mario/MuriendoState.hpp: ${SRC}/model/mario/MarioState.hpp
${SRC}/model/mario/SueloState.hpp: ${SRC}/model/mario/MarioState.hpp
${SRC}/model/mario/TrepandoState.hpp: ${SRC}/model/mario/MarioState.hpp
${SRC}/model/mario/MarioState.hpp: ${SRC}/model/stage/Stage.hpp
${SRC}/model/mario/AudioObserver.hpp: ${SRC}/utils/marioStructs.hpp
${SRC}/model/stage/Ladder.hpp: ${SRC}/utils/fixed_point.hpp
${SRC}/model/stage/MovingPlatform.hpp: ${SRC}/utils/Constants.hpp ${SRC}/utils/punto.hpp
${SRC}/model/stage/Platform.hpp: ${SRC}/utils/punto.hpp
${SRC}/model/stage/Stage.hpp: ${SRC}/model/stage/Tile.hpp ${SRC}/model/stage/Ladder.hpp ${SRC}/model/stage/Platform.hpp ${SRC}/model/stage/MovingPlatform.hpp ${SRC}/utils/Constants.hpp
${SRC}/model/stage/Tile.hpp: ${SRC}/model/stage/Ladder.hpp ${SRC}/model/stage/Platform.hpp ${SRC}/model/stage/MovingPlatform.hpp

${SRC}/view/Client.hpp: ${SRC}/utils/user.hpp ${SRC}/utils/exitStatus.hpp ${SRC}/view/SceneVista.hpp
${SRC}/view/BarrilVista.hpp: ${SRC}/utils/punto.hpp
${SRC}/view/EnemigoFuegoVista.hpp: ${SRC}/utils/punto.hpp
${SRC}/view/HammerVista.hpp: ${SRC}/utils/punto.hpp
${SRC}/view/InterludeVista.hpp: ${SRC}/view/SceneVista.hpp
${SRC}/view/MarioVista.hpp: ${SRC}/utils/marioStructs.hpp
${SRC}/view/Nivel1Vista.hpp: ${SRC}/view/NivelVista.hpp ${SRC}/view/EnemigoFuegoVista.hpp ${SRC}/view/PoleaVista.hpp ${SRC}/view/FuegoVista.hpp
${SRC}/view/Nivel2Vista.hpp: ${SRC}/view/NivelVista.hpp ${SRC}/view/BarrilVista.hpp ${SRC}/view/FuegoVista.hpp
${SRC}/view/NivelVista.hpp: ${SRC}/view/SceneVista.hpp ${SRC}/view/MarioVista.hpp ${SRC}/view/StatsVista.hpp ${SRC}/view/PaulineVista.hpp ${SRC}/view/DonkeyKongVista.hpp
${SRC}/view/PlataformaMovilVista.hpp: ${SRC}/utils/punto.hpp
${SRC}/view/SceneVista.hpp: ${SRC}/utils/estadoJuego.hpp
${SRC}/view/StartPageView.hpp: ${SRC}/utils/user.hpp
${SRC}/view/StatsVista.hpp: ${SRC}/utils/estadoJuego.hpp ${SRC}/utils/Constants.hpp
${SRC}/view/TextRenderer.hpp: ${SRC}/utils/punto.hpp

${SRC}/utils/dimensiones.hpp: ${SRC}/utils/fixed_point.hpp
${SRC}/utils/estadoJuego.hpp: ${SRC}/utils/punto.hpp ${SRC}/utils/marioStructs.hpp ${SRC}/utils/Constants.hpp
${SRC}/utils/marioStructs.hpp: ${SRC}/utils/punto.hpp ${SRC}/utils/fixed_point.hpp
${SRC}/utils/punto.hpp: ${SRC}/utils/fixed_point.hpp

deps:
	${PKGS}

format:
	xargs clang-format -i < .clang-files

update-format:
	find src -name "*.[ch]pp" >.clang-files

clean:
	-rm ${BIN}/% ${OBJ}/%.o ${OBJ}/server/%.o ${OBJ}/client/%.o

.PHONY: all deps format update-format clean
