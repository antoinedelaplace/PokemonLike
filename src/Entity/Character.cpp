#include <iostream>
#include "Character.hh"
#include "PlayerEntity.hh"
#include "../Game.hh"

Character::Character() : AbstractEntity() {}

Character::~Character(){}

void Character::Draw() {}

void Character::Update() {}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    PlayerEntity &pm = PlayerEntity::getInstance();
    states.texture = &ResourceManager::GetInstance().getPersoTileset();

    sf::VertexArray quad(sf::Quads, 4);
    Game &game = Game::GetInstance();
    if (game.getState()==BUILDING) {
        quad[0].position = sf::Vector2f(pm.getX() - 28, pm.getY() - 40);
        quad[1].position = sf::Vector2f(pm.getX(), pm.getY() - 40);
        quad[2].position = sf::Vector2f(pm.getX(), pm.getY());
        quad[3].position = sf::Vector2f(pm.getX() - 28, pm.getY());
    }
    else {
        quad[0].position = sf::Vector2f(pm.getX() - 14, pm.getY() - 20);
        quad[1].position = sf::Vector2f(pm.getX(), pm.getY() - 20);
        quad[2].position = sf::Vector2f(pm.getX(), pm.getY());
        quad[3].position = sf::Vector2f(pm.getX() - 14, pm.getY());
    }
    std::vector<int> coord = pm.getCoord();

    quad[0].texCoords = sf::Vector2f(coord[0], coord[1]);
    quad[1].texCoords = sf::Vector2f(coord[0]+14, coord[1]);
    quad[2].texCoords = sf::Vector2f(coord[0]+14, coord[1]+20);
    quad[3].texCoords = sf::Vector2f(coord[0], coord[1]+20);

    sf::Transform transform;
    states.transform = transform;
    target.draw(quad, states);
}









