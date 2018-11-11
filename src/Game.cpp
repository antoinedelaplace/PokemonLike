#include "Game.hh"

Game* Game::instance = new Game();

Game& Game::GetInstance() {
    return (*instance);
}

Game::Game() {
    state = WORLD;
}

Game::~Game() {}

const int Game::getWindowWidth() const {
    return windowWidth;
}

const int Game::getWindowHeight() const {
    return windowHeight;
}


int Game::isAFight() {
    srand(time(NULL));
    if((rand() % 10) == 1) { // 1 chance sur 10
        state = FIGHT;
        return (1);
    }
    else
        return (0);
}

int Game::start() {
    Map &map = Map::GetInstance();
    ResourceManager &rm = ResourceManager::GetInstance();
    PlayerEntity &pm = PlayerEntity::getInstance();
    InputManager &im = InputManager::getInstance();
    TimeManager &tm = TimeManager::GetInstance();
    World &world = World::getInstance();
    FPS &fp = FPS::getInstance();
    im.AddObserver(&fp);
    im.AddObserver(&world);

    Fight *fight = NULL;

    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pokemon");

    //On charge les ressources
    if (!rm.load())
        return (-1);

    // on crée la Map
    map.load(sf::Vector2u(tiledSize, tiledSize), horizontalTiledNumber, verticalTiledNumber);

    //On lance la musique
    rm.getMainMusic().play();
    tm.Start();
    // on fait tourner la boucle principale
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        if (tm.GetStartedTime() >= 1000) {
            tm.Start();
        }
        sf::Event event;
        if (pm.getIsMoving() != 0) {
            pm.setIsMoving();
            while (window.pollEvent(event));
        }
        else {
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case (sf::Event::Closed):
                        window.close();
                        break;
                    default:
                        im.move(event);
                }
                break;
            }
        }
        switch (state) {
            case (WORLD):
                if (fight != NULL) {
                    im.RemoveObserver(fight);
                    fight->free();
                    fight = NULL;
                }
                window.draw(world);
                break;
            case (FIGHT):
                if (fight == NULL) {
                    fight = new Fight();
                    im.AddObserver(fight);
                }
                window.draw(*fight);
                break;

            case (BUILDING):
                window.draw(*building);
        }
        if (this->FPSGame)
            window.draw(fp);
        window.display();
        tm.Update();
    }
    delete fight;
    this->freeGame();
    return (1);
}

int Game::isFPS() {
    if (this->FPSGame == 0)
        this->FPSGame = 1;
    else
        this->FPSGame = 0;
    return this->FPSGame;
}

void Game::freeGame() {
    ResourceManager::free();
    InputManager::free();
    ListObjects::free();
    ListPokemon::free();
    ListAttack::free();
    PlayerEntity::free();
    Map::free();
    FPS::free();
    TimeManager::free();
}

void Game::free() {
    delete instance;
}

GameState Game::getState() const {
    return state;
}

void Game::setState(GameState state) {
    Game::state = state;
}

void Game::setBuilding(Buildings *building) {
    InputManager &im = InputManager::getInstance();
    im.AddObserver(building);
    state = BUILDING;
    Game::building = building;
}




