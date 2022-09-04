CXX		:= g++
CXX_FLAGS	:= -std=c++20 -O3 -flto=auto

SCFLAGS		:= $(shell pkg-config --cflags fmt jsoncpp) -fconcepts
CCFLAGS		:= $(shell pkg-config --cflags \
		   sdl2 SDL2_mixer SDL2_image fmt jsoncpp) -fconcepts
WARNINGS	:= 

BIN		:= bin
OBJ		:= obj
SRC		:= src

SLIBS		:= $(shell pkg-config --libs fmt jsoncpp) -pthread
CLIBS		:= $(shell pkg-config --libs sdl2 \
		   SDL2_mixer SDL2_image fmt jsoncpp) -pthread -latomic

PKGS		:= $(shell command -v apt-get && \
		   echo install build-essential \
		   libsdl2-2.0 libsdl2-dev \
		   libsdl2-image-2.0-0 libsdl2-image-dev \
		   libsdl2-mixer-dev libjsoncpp-dev || \
		   command -v pacman && \
		   echo -S sdl2 sdl2_image sdl2_mixer jsoncpp)

OBJS	:= ${OBJ}/configuration.o ${OBJ}/logger.o ${OBJ}/dataTransfer.o
OBJSS	:= ${OBJ}/server/main.o ${OBJ}/server/Server.o \
	   ${OBJ}/server/tcp_server.o ${OBJ}/server/Barril.o \
	   ${OBJ}/server/EnemigoFuego.o ${OBJ}/server/Mario.o \
	   ${OBJ}/server/Nivel1.o ${OBJ}/server/Nivel2.o \
	   ${OBJ}/server/AireState.o ${OBJ}/server/GameOverState.o \
	   ${OBJ}/server/LevelCompletedState.o ${OBJ}/server/MarioState.o \
	   ${OBJ}/server/MuriendoState.o ${OBJ}/server/SueloState.o \
	   ${OBJ}/server/TrepandoState.o ${OBJ}/server/MovingPlatform.o \
	   ${OBJ}/server/Stage.o
OBJSC	:= ${OBJ}/client/main.o ${OBJ}/client/Client.o \
	   ${OBJ}/client/textureHandler.o ${OBJ}/client/AudioController.o \
	   ${OBJ}/client/MarioController.o ${OBJ}/client/BarrilVista.o \
	   ${OBJ}/client/DonkeyKongVista.o ${OBJ}/client/EnemigoFuegoVista.o \
	   ${OBJ}/client/FuegoVista.o ${OBJ}/client/HammerVista.o \
	   ${OBJ}/client/InterludeVista.o ${OBJ}/client/MarioVista.o \
	   ${OBJ}/client/Nivel1Vista.o ${OBJ}/client/Nivel2Vista.o \
	   ${OBJ}/client/NivelVista.o ${OBJ}/client/PaulineVista.o \
	   ${OBJ}/client/PlataformaMovilVista.o ${OBJ}/client/PoleaVista.o \
	   ${OBJ}/client/showMessage.o ${OBJ}/client/StartPageView.o \
	   ${OBJ}/client/StatsVista.o ${OBJ}/client/TextRenderer.o

configuration			:= ${SRC}/configuration.hpp
logger				:= ${SRC}/logger.hpp

utils-data-transfer	:= ${SRC}/utils/dataTransfer.hpp
utils-player		:= ${SRC}/utils/player.hpp
utils-fixed-point	:= ${SRC}/utils/fixed_point.hpp
utils-tcp-server	:= ${SRC}/utils/tcp_server.hpp
utils-texture-handler	:= ${SRC}/utils/textureHandler.hpp
utils-user		:= ${SRC}/utils/user.hpp
utils-exit-status	:= ${SRC}/utils/exitStatus.hpp
utils-constants		:= ${SRC}/utils/Constants.hpp
utils-punto		:= ${SRC}/utils/punto.hpp $(utils-fixed-point)
utils-dimensiones	:= ${SRC}/utils/dimensiones.hpp $(utils-fixed-point)
utils-mario-structs	:= ${SRC}/utils/marioStructs.hpp $(utils-punto) $(utils-fixed-point)
utils-estado-juego	:= ${SRC}/utils/estadoJuego.hpp $(utils-punto) $(utils-mario-structs) $(utils-constants)

model-server			:= ${SRC}/model/Server.hpp $(utils-player) $(utils-user)
model-barril			:= ${SRC}/model/Barril.hpp $(utils-constants) $(utils-dimensiones) $(utils-punto)
model-enemigo-fuego		:= ${SRC}/model/EnemigoFuego.hpp $(utils-constants) $(utils-dimensiones) $(utils-punto)
model-entidad			:= ${SRC}/model/Entidad.hpp $(utils-punto)
model-hammer			:= ${SRC}/model/Hammer.hpp $(utils-fixed-point) $(utils-punto) $(utils-dimensiones)
model-scene			:= ${SRC}/model/Scene.hpp $(utils-estado-juego)
model-mario-audio-observer	:= ${SRC}/model/mario/AudioObserver.hpp $(utils-mario-structs)
model-stage-ladder		:= ${SRC}/model/stage/Ladder.hpp $(utils-fixed-point)
model-stage-moving-platform	:= ${SRC}/model/stage/MovingPlatform.hpp $(utils-constants) $(utils-punto)
model-stage-platform		:= ${SRC}/model/stage/Platform.hpp $(utils-punto)

model-interlude			:= ${SRC}/model/Interlude.hpp $(model-scene)
model-stage-tile		:= ${SRC}/model/stage/Tile.hpp $(model-stage-ladder) $(model-stage-platform) $(model-stage-moving-platform)
model-stage-stage		:= ${SRC}/model/stage/Stage.hpp $(model-stage-tile) $(model-stage-ladder) $(model-stage-platform) $(model-stage-moving-platform) $(utils-constants)

model-mario-mario-state		:= ${SRC}/model/mario/MarioState.hpp $(model-stage-stage)
model-mario-aire-state		:= ${SRC}/model/mario/AireState.hpp $(model-mario-mario-state)
model-mario-game-over-state	:= ${SRC}/model/mario/GameOverState.hpp $(model-mario-mario-state)
model-mario-level-completed-state	:= ${SRC}/model/mario/LevelCompletedState.hpp $(model-mario-mario-state)
model-mario-muriendo-state	:= ${SRC}/model/mario/MuriendoState.hpp $(model-mario-mario-state)
model-mario-suelo-state		:= ${SRC}/model/mario/SueloState.hpp $(model-mario-mario-state)
model-mario-trepando-state	:= ${SRC}/model/mario/TrepandoState.hpp $(model-mario-mario-state)

model-mario			:= ${SRC}/model/Mario.hpp $(model-mario-mario-state) $(model-mario-audio-observer) $(model-entidad) $(model-hammer) $(utils-mario-structs) $(utils-punto)
model-nivel			:= ${SRC}/model/Nivel.hpp $(model-scene) $(model-stage-stage) $(model-mario) $(model-hammer)
model-nivel1			:= ${SRC}/model/Nivel1.hpp $(model-stage-moving-platform) $(model-enemigo-fuego) $(model-nivel)
model-nivel2			:= ${SRC}/model/Nivel2.hpp $(model-barril) $(model-nivel)

controller-audio-controller	:= ${SRC}/controller/AudioController.hpp
controller-mario-controller	:= ${SRC}/controller/MarioController.hpp

view-donkey-kong-vista		:= ${SRC}/view/DonkeyKongVista.hpp
view-fuego-vista		:= ${SRC}/view/FuegoVista.hpp
view-pauline-vista		:= ${SRC}/view/PaulineVista.hpp
view-polea-vista		:= ${SRC}/view/PoleaVista.hpp
view-show-message		:= ${SRC}/view/showMessage.hpp

view-barril-vista		:= ${SRC}/view/BarrilVista.hpp $(utils-punto)
view-enemigo-fuego-vista	:= ${SRC}/view/EnemigoFuegoVista.hpp $(utils-punto)
view-hammer-vista		:= ${SRC}/view/HammerVista.hpp $(utils-punto)
view-mario-vista		:= ${SRC}/view/MarioVista.hpp $(utils-mario-structs)
view-plataforma-movil-vista	:= ${SRC}/view/PlataformaMovilVista.hpp $(utils-punto)
view-scene-vista		:= ${SRC}/view/SceneVista.hpp $(utils-estado-juego)
view-start-page-view		:= ${SRC}/view/StartPageView.hpp $(utils-user)
view-stats-vista		:= ${SRC}/view/StatsVista.hpp $(utils-estado-juego) $(utils-constants)
view-text-renderer		:= ${SRC}/view/TextRenderer.hpp $(utils-punto)

view-client			:= ${SRC}/view/Client.hpp $(utils-user) $(utils-exit-status) $(view-scene-vista)
view-interlude-vista		:= ${SRC}/view/InterludeVista.hpp $(view-scene-vista)
view-nivel-vista		:= ${SRC}/view/NivelVista.hpp $(view-scene-vista) $(view-mario-vista) $(view-stats-vista) $(view-pauline-vista) $(view-donkey-kong-vista)
view-nivel1-vista		:= ${SRC}/view/Nivel1Vista.hpp $(view-nivel-vista) $(view-enemigo-fuego-vista) $(view-polea-vista) $(view-fuego-vista)
view-nivel2-vista		:= ${SRC}/view/Nivel2Vista.hpp $(view-nivel-vista) $(view-barril-vista) $(view-fuego-vista)

all: ${BIN}/server ${BIN}/client

${BIN}/server: ${OBJS} ${OBJSS}
	mkdir -p bin
	${CXX} ${CXX_FLAGS} ${WARNINGS} $^ -o $@ ${SLIBS} ${SCFLAGS}
 
${BIN}/client: ${OBJS} ${OBJSC}
	mkdir -p bin
	${CXX} ${CXX_FLAGS} ${WARNINGS} $^ -o $@ ${CLIBS} ${CCFLAGS}

${OBJ}/configuration.o: ${SRC}/configuration.cpp $(configuration) $(logger)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/logger.o: ${SRC}/logger.cpp $(logger)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/dataTransfer.o: ${SRC}/utils/dataTransfer.cpp $(utils-data-transfer)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/main.o: ${SRC}/main/main_server.cpp $(configuration) $(logger) $(model-server) $(utils-tcp-server)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Server.o: ${SRC}/model/Server.cpp $(model-server) $(configuration) $(logger) $(model-interlude) $(model-nivel1) $(model-nivel2) $(model-mario) $(utils-constants) $(utils-data-transfer) $(utils-estado-juego) $(utils-player) $(utils-tcp-server)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/tcp_server.o: ${SRC}/utils/tcp_server.cpp $(utils-tcp-server)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Barril.o: ${SRC}/model/Barril.cpp $(model-barril)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/EnemigoFuego.o: ${SRC}/model/EnemigoFuego.cpp $(model-enemigo-fuego)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Mario.o: ${SRC}/model/Mario.cpp $(model-mario) $(model-mario-suelo-state) $(model-mario-muriendo-state) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Nivel1.o: ${SRC}/model/Nivel1.cpp $(model-nivel1) $(model-entidad) $(configuration) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Nivel2.o: ${SRC}/model/Nivel2.cpp $(model-nivel2) $(model-entidad) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/AireState.o: ${SRC}/model/mario/AireState.cpp $(model-mario-aire-state) $(model-mario-suelo-state) $(model-mario-muriendo-state) $(model-mario) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/GameOverState.o: ${SRC}/model/mario/GameOverState.cpp $(model-mario-game-over-state) $(model-mario)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/LevelCompletedState.o: ${SRC}/model/mario/LevelCompletedState.cpp $(model-mario-level-completed-state) $(model-mario)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/MarioState.o: ${SRC}/model/mario/MarioState.cpp $(model-mario-mario-state) $(model-mario-suelo-state) $(model-mario) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/MuriendoState.o: ${SRC}/model/mario/MuriendoState.cpp $(model-mario-muriendo-state) $(model-mario-game-over-state) $(model-mario-suelo-state) $(model-mario)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/SueloState.o: ${SRC}/model/mario/SueloState.cpp $(model-mario-suelo-state) $(model-mario-aire-state) $(model-mario-trepando-state) $(model-mario) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/TrepandoState.o: ${SRC}/model/mario/TrepandoState.cpp $(model-mario-trepando-state) $(model-mario-suelo-state) $(model-mario-level-completed-state) $(model-mario)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/MovingPlatform.o: ${SRC}/model/stage/MovingPlatform.cpp $(model-stage-moving-platform)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/server/Stage.o: ${SRC}/model/stage/Stage.cpp $(model-stage-stage)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/main.o: ${SRC}/main/main_client.cpp $(configuration) $(logger) $(view-client)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/Client.o: ${SRC}/view/Client.cpp $(view-client) $(view-nivel1-vista) $(view-nivel2-vista) $(view-interlude-vista) $(view-start-page-view) $(view-show-message) $(configuration) $(logger) $(controller-audio-controller) $(controller-mario-controller) $(utils-constants) $(utils-estado-juego) $(utils-data-transfer) $(utils-texture-handler)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/textureHandler.o: ${SRC}/utils/textureHandler.cpp $(utils-texture-handler) $(logger) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/AudioController.o: ${SRC}/controller/AudioController.cpp $(controller-audio-controller) $(logger) $(utils-mario-structs)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/MarioController.o: ${SRC}/controller/MarioController.cpp $(controller-mario-controller) $(controller-audio-controller)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/BarrilVista.o: ${SRC}/view/BarrilVista.cpp $(view-barril-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/DonkeyKongVista.o: ${SRC}/view/DonkeyKongVista.cpp $(view-donkey-kong-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/EnemigoFuegoVista.o: ${SRC}/view/EnemigoFuegoVista.cpp $(view-enemigo-fuego-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/FuegoVista.o: ${SRC}/view/FuegoVista.cpp $(view-fuego-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/HammerVista.o: ${SRC}/view/HammerVista.cpp $(view-hammer-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/InterludeVista.o: ${SRC}/view/InterludeVista.cpp $(view-interlude-vista) $(view-text-renderer) $(configuration) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/MarioVista.o: ${SRC}/view/MarioVista.cpp $(view-mario-vista) $(view-hammer-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/Nivel1Vista.o: ${SRC}/view/Nivel1Vista.cpp $(view-nivel1-vista) $(view-plataforma-movil-vista) $(view-hammer-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/Nivel2Vista.o: ${SRC}/view/Nivel2Vista.cpp $(view-nivel2-vista) $(view-hammer-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/NivelVista.o: ${SRC}/view/NivelVista.cpp $(view-nivel-vista) $(configuration) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/PaulineVista.o: ${SRC}/view/PaulineVista.cpp $(view-pauline-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/PlataformaMovilVista.o: ${SRC}/view/PlataformaMovilVista.cpp $(view-plataforma-movil-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/PoleaVista.o: ${SRC}/view/PoleaVista.cpp $(view-polea-vista) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/showMessage.o: ${SRC}/view/showMessage.cpp $(view-show-message) $(view-text-renderer) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/StartPageView.o: ${SRC}/view/StartPageView.cpp $(view-start-page-view) $(view-text-renderer) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/StatsVista.o: ${SRC}/view/StatsVista.cpp $(view-stats-vista) $(view-text-renderer) $(configuration)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

${OBJ}/client/TextRenderer.o: ${SRC}/view/TextRenderer.cpp $(view-text-renderer) $(utils-constants)
	${CXX} ${CXX_FLAGS} ${WARNINGS} -c $< -o $@

deps:
	${PKGS}

format:
	xargs clang-format -i < .clang-files

update-format:
	find src -name "*.[ch]pp" >.clang-files

clean:
	-rm ${BIN}/* ${OBJ}/*.o ${OBJ}/server/*.o ${OBJ}/client/*.o

.PHONY: all deps format update-format clean
