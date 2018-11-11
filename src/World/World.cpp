//
// Created by Benoît - Xavier HOUVET on 28/04/2017.
//

#include "World.hh"

World* World::instance = new World();

World::World() : IObserver() {
    ListAttack &la = ListAttack::GetInstance();
    ListPokemon &lp = ListPokemon::GetInstance();
    PlayerEntity &pm = PlayerEntity::getInstance();
    la.Start();
    lp.Start();
    pm.initPokemons();
    Game &game = Game::GetInstance();
}

World::~World() {}

void World::Notify(char i) {
    Map &map = Map::GetInstance();
    Game &game = Game::GetInstance();
    PlayerEntity &pm = PlayerEntity::getInstance();
    if (game.getState() == WORLD) {
        switch (i) {
            case ('Z'):
                if (!pm.turn(i) && map.isValidTile((pm.getX() / 16) - 1, ((pm.getY() - 16) / 16) - 1)) {
                    pm.setIsMoving();
                    if ((map.isFightTile((pm.getX() / 16) - 1, ((pm.getY() - 16) / 16) - 1)))
                        game.isAFight();
                }
                break;
            case ('S'):
                if (!pm.turn(i) && map.isValidTile((pm.getX() / 16) - 1, ((pm.getY() + 16) / 16) - 1)) {
                    pm.setIsMoving();
                    if ((map.isFightTile((pm.getX() / 16) - 1, ((pm.getY() + 16) / 16) - 1)))
                        game.isAFight();
                }
                break;
            case ('Q'):
                if (!pm.turn(i) && map.isValidTile(((pm.getX() - 16) / 16) - 1, (pm.getY() / 16) - 1)) {
                    pm.setIsMoving();
                    if ((map.isFightTile(((pm.getX() - 16) / 16) - 1, (pm.getY() / 16) - 1)))
                        game.isAFight();
                }
                break;
            case ('D'):
                if (!pm.turn(i) && map.isValidTile(((pm.getX() + 16) / 16) - 1, (pm.getY() / 16) - 1)) {
                    pm.setIsMoving();
                    if ((map.isFightTile(((pm.getX() + 16) / 16) - 1, (pm.getY() / 16) - 1)))
                        game.isAFight();
                }
                break;
            case ('P'):
                pm.turn(i);
        }
    }
}

World& World::getInstance() {
    return *instance;
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Map &map = Map::GetInstance();
    PlayerEntity &pm = PlayerEntity::getInstance();
    target.draw(map, states);
    target.draw(pm, states);
}

