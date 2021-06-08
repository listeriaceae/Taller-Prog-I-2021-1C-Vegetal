#include "Nivel1.h"
#include "nivel/Escalera.h"

const int ESCALERA_1_X0 = 24;
const int ESCALERA_1_X1 = 32;
const int ESCALERA_1_Y0 = 232;
const int ESCALERA_1_Y1 = 184;

const int ESCALERA_2_X0 = 208;
const int ESCALERA_2_X1 = 216;
const int ESCALERA_2_Y0 = 184;
const int ESCALERA_2_Y1 = 144;

const int ESCALERA_3_X0 = -8;
const int ESCALERA_3_X1 = 0;
const int ESCALERA_3_Y0 = 144;
const int ESCALERA_3_Y1 = 104;

const int ESCALERA_4_X0 = 208;
const int ESCALERA_4_X1 = 216;
const int ESCALERA_4_Y0 = 104;
const int ESCALERA_4_Y1 = 72;

const int ESCALERA_5_X0 = 120;
const int ESCALERA_5_X1 = 128;
const int ESCALERA_5_Y0 = 72;
const int ESCALERA_5_Y1 = 40;

Nivel1::Nivel1() : Nivel() {
    this->initPlataformas();
    this->inicializarEscaleras();
}

void Nivel1::initPlataformas() {
    plataformasMoviles.push_back(new PlataformaMovil(0, 0));
    plataformasMoviles.push_back(new PlataformaMovil(1, 0));
    plataformasMoviles.push_back(new PlataformaMovil(2, 0));

    plataformasMoviles.push_back(new PlataformaMovil(0, 1));
    plataformasMoviles.push_back(new PlataformaMovil(1, 1));
    plataformasMoviles.push_back(new PlataformaMovil(2, 1));

    plataformasMoviles.push_back(new PlataformaMovil(0, 2));
    plataformasMoviles.push_back(new PlataformaMovil(1, 2));
    plataformasMoviles.push_back(new PlataformaMovil(2, 2));

    plataformasMoviles.push_back(new PlataformaMovil(0, 3));
    plataformasMoviles.push_back(new PlataformaMovil(1, 3));
    plataformasMoviles.push_back(new PlataformaMovil(2, 3));

    this->plataformas.push_back(new Plataforma(0, 248, 48, 248));
    this->plataformas.push_back(new Plataforma(64, 248, 88, 248));
    this->plataformas.push_back(new Plataforma(104, 248, 128, 248));
    this->plataformas.push_back(new Plataforma(144, 248, 168, 248));
    this->plataformas.push_back(new Plataforma(184, 248, 224, 248));
    this->plataformas.push_back(new Plataforma(0, 200, 48, 200));
    this->plataformas.push_back(new Plataforma(64, 200, 88, 200));
    this->plataformas.push_back(new Plataforma(104, 200, 128, 200));
    this->plataformas.push_back(new Plataforma(144, 200, 168, 200));
    this->plataformas.push_back(new Plataforma(184, 200, 224, 200));
    this->plataformas.push_back(new Plataforma(0, 160, 16, 160));
    this->plataformas.push_back(new Plataforma(208, 160, 224, 160));
    this->plataformas.push_back(new Plataforma(0, 120, 16, 120));
    this->plataformas.push_back(new Plataforma(208, 120, 224, 120));
    this->plataformas.push_back(new Plataforma(208, 88, 224, 88));
    this->plataformas.push_back(new Plataforma(160, 87, 192, 87));
    this->plataformas.push_back(new Plataforma(24, 84, 144, 84));
    this->plataformas.push_back(new Plataforma(88, 56, 136, 56));
}

void Nivel1::update() {
    updatePlatforms();
    updateEnemies();
    updatePlayers();
}

void Nivel1::updatePlatforms() {
    std::list<PlataformaMovil*>::iterator it;
    for (it = plataformasMoviles.begin(); it != plataformasMoviles.end(); ++it) {
        (*it)->mover();
    }
}

estadoNivel_t* Nivel1::getEstado() {
    estadoNivel_t *estado = new estadoNivel_t();

    for (EnemigoFuego *enemy : this->enemies) {
        estado->enemies.push_back(enemy->getPos());
    }
    for (PlataformaMovil *plataforma : this->plataformasMoviles) {
        estado->platforms.push_back(plataforma->getPos());
    }
    for (Mario *player : this->jugadores) {
        estado->players.push_back(player->getEstado());
    }
    return estado;
}

Nivel1::~Nivel1() {
    std::list<PlataformaMovil*>::iterator it;
    for (it = plataformasMoviles.begin(); it != plataformasMoviles.end(); ++it) delete (*it);

    plataformasMoviles.clear();
}

void Nivel1::inicializarEscaleras() {
    Escalera * e1 = new Escalera("E1",
                                ESCALERA_1_X1 -4,
                                ESCALERA_1_X0,
                                ESCALERA_1_X1,
                                ESCALERA_1_Y0,
                                ESCALERA_1_Y1);
    Escalera * e2 = new Escalera("E2",
                                ESCALERA_2_X1 -4,
                                ESCALERA_2_X0,
                                ESCALERA_2_X1,
                                ESCALERA_2_Y0,
                                ESCALERA_2_Y1);
    Escalera * e3 = new Escalera("E3",
                                ESCALERA_3_X1 -4,
                                ESCALERA_3_X0,
                                ESCALERA_3_X1,
                                ESCALERA_3_Y0,
                                ESCALERA_3_Y1);
    Escalera * e4 = new Escalera("E4",
                                ESCALERA_4_X1 -4,
                                ESCALERA_4_X0,
                                ESCALERA_4_X1,
                                ESCALERA_4_Y0,
                                ESCALERA_4_Y1);
    Escalera * e5 = new Escalera("E5",
                                ESCALERA_5_X1 -4,
                                ESCALERA_5_X0,
                                ESCALERA_5_X1,
                                ESCALERA_5_Y0,
                                ESCALERA_5_Y1);
    
    this->escaleras[0] = e1;
    this->escaleras[1] = e2;
    this->escaleras[2] = e3;
    this->escaleras[3] = e4;
    this->escaleras[4] = e5;
}

Escalera* Nivel1::getEscalera(punto_t p) {
    if (p.x >= ESCALERA_1_X0 
        && p.x <= ESCALERA_1_X1 
        && p.y <= ESCALERA_1_Y0
        && p.y >= ESCALERA_1_Y1) {
            return this->escaleras[0];
    } else if (p.x >= ESCALERA_2_X0 
        && p.x <= ESCALERA_2_X1 
        && p.y <= ESCALERA_2_Y0
        && p.y >= ESCALERA_2_Y1) {
            return this->escaleras[1];
    } else if (p.x >= ESCALERA_3_X0 
        && p.x <= ESCALERA_3_X1 
        && p.y <= ESCALERA_3_Y0
        && p.y >= ESCALERA_3_Y1) {
            return this->escaleras[2];
    } else if (p.x >= ESCALERA_4_X0 
        && p.x <= ESCALERA_4_X1 
        && p.y <= ESCALERA_4_Y0
        && p.y >= ESCALERA_4_Y1) {
            return this->escaleras[3];
    } else if (p.x >= ESCALERA_5_X0 
        && p.x <= ESCALERA_5_X1 
        && p.y <= ESCALERA_5_Y0
        && p.y >= ESCALERA_5_Y1) {
            return this->escaleras[4];
    }
    return NULL;
}