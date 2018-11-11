#ifndef FIRST_GAME_HH
#define FIRST_GAME_HH

#include "Manager/ResourceManager.hh"
#include "Map/Map.hh"
#include "Entity/PlayerEntity.hh"
#include "Entity/Character.hh"
#include "Manager/InputManager.hh"
#include "Manager/TimeManager.hh"
#include "Fight/Fight.hh"
#include "List/ListPokemon.hh"
#include "List/ListAttack.hh"
#include "List/ListObjects.hh"
#include "Utils/FPS.hh"
#include "Building/Buildings.hh"
#include "World/World.hh"

enum GameState { WORLD, FIGHT, BUILDING};

class Game  {
public:
    static Game& GetInstance();
    int start();
    int isAFight();
    const int getWindowWidth() const;
    const int getWindowHeight() const;
    int isFPS();
    void freeGame();
    static void free();
    GameState getState() const;
    void setState(GameState state);
    void setBuilding(Buildings *building);
private:
    static Game* instance;
    Game();
    ~Game();
    GameState state;
    Buildings* building;
    int FPSGame = 0;
    const int tiledSize = 16;
    const int horizontalTiledNumber = 33;
    const int verticalTiledNumber = 53;
    const int windowWidth = tiledSize * horizontalTiledNumber;
    const int windowHeight = tiledSize * verticalTiledNumber;
};


#endif //FIRST_GAME_HH
