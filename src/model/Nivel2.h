#include <string>
#include <list>
#include <SDL2/SDL.h>
#include <vector>
#include "Barril.h"

using namespace std;
const int MAX_BARRELS = 15;
const std::string DEFAULT_IMAGE = "res/default.png";

class Nivel2 {
    public:
        Nivel2(SDL_Renderer*);
        void updateView ();
        void addElement (Entidad*);
        void setBackground (std::string background);
        void initialize();
    private:
        std::string backgroundImage = DEFAULT_IMAGE;
        vector<Barril> barrels;
        list<Entidad*> elements;
        Uint32 tickLastBarrel;
        string path;
        SDL_Renderer* renderer;
        SDL_Surface* background_surface;
        SDL_Texture* background_texture;
        void loadBackground ();
        void updateBackground ();
        void loadElements ();
        void updateElements ();
        void addBarrel ();
        void updateBarrels ();
};