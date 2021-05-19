#include <string>
#include <list>
#include <SDL2/SDL.h>
#include <vector>
#include "Barril.h"

using namespace std;
const int MAX_BARRELS = 15;

class Level2 {
    public:
        Level2(SDL_Renderer*);
        void updateView ();
        void addElement (Entidad*);
    private:
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