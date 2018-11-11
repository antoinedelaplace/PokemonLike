//
// Created by Benoît - Xavier HOUVET on 30/03/2017.
//

#include "PlayerEntity.hh"
#include "../List/ListPokemon.hh"
#include "../Map/Map.hh"
#include "../Game.hh"
#include "../Building/BuildingFactory.hh"

PlayerEntity* PlayerEntity::instance = new PlayerEntity();

PlayerEntity& PlayerEntity::getInstance() {
    return *instance;
}

PlayerEntity::PlayerEntity()  {
    this->X = 160;
    this->Y = 160;
    this->direction = "S";
    this->coord = this->getSpriteCoord(this->direction);
    this->isMoving = 0;
    this->m_inventaire = new Bag();
}

PlayerEntity::~PlayerEntity() {}

int PlayerEntity::getX() const {
    return X;
}

int PlayerEntity::getY() const {
    return Y;
}

const std::vector<int> &PlayerEntity::getCoord() const {
    return coord;
}

void PlayerEntity::setCoord(const std::vector<int> &coord) {
    PlayerEntity::coord = coord;
}

std::string PlayerEntity::getDirection() {
    return direction;
}

void PlayerEntity::setDirection(std::string direction) {
    PlayerEntity::direction = direction;
}

std::vector<int> PlayerEntity::getSpriteCoord(std::string direction) {
    std::vector<int> tmp;
    if (direction == "S") {
        tmp.push_back(8);
        tmp.push_back(8);
        return tmp;
    }
    if (direction == "N") {
        tmp.push_back(60);
        tmp.push_back(8);
        return tmp;
    }
    if (direction == "E") {
        tmp.push_back(112);
        tmp.push_back(10);
        return tmp;
    }
    else {
        tmp.push_back(165);
        tmp.push_back(9);
        return tmp;
    }
}

std::vector<int> PlayerEntity::getSpriteCoordMoveFirst(std::string direction) {
    std::vector<int> tmp;
    if (direction == "S") {
        tmp.push_back(26);
        tmp.push_back(8);
        return tmp;
    }
    if (direction == "N") {
        tmp.push_back(78);
        tmp.push_back(9);
        return tmp;
    }
    if (direction == "E") {
        tmp.push_back(129);
        tmp.push_back(10);
        return tmp;
    }
    else {
        tmp.push_back(183);
        tmp.push_back(9);
        return tmp;
    }
}

std::vector<int> PlayerEntity::getSpriteCoordMoveSecond(std::string) {
    std::vector<int> tmp;
    if (direction == "S") {
        tmp.push_back(43);
        tmp.push_back(8);
        return tmp;
    }
    if (direction == "N") {
        tmp.push_back(96);
        tmp.push_back(9);
        return tmp;
    }
    if (direction == "E") {
        tmp.push_back(146);
        tmp.push_back(10);
        return tmp;
    }
    else {
        tmp.push_back(201);
        tmp.push_back(9);
        return tmp;
    }
}

void PlayerEntity::moveUp() {
    PlayerEntity::Y -= 1;
}

void PlayerEntity::moveDown() {
    PlayerEntity::Y += 1;
}

void PlayerEntity::moveLeft() {
    PlayerEntity::X -= 1;
}

void PlayerEntity::moveRight() {
    PlayerEntity::X += 1;
}

void PlayerEntity::move() {
    if (PlayerEntity::direction == "N")
        PlayerEntity::moveUp();
    else if (PlayerEntity::direction == "S")
        PlayerEntity::moveDown();
    else if (PlayerEntity::direction == "E")
        PlayerEntity::moveRight();
    else
        PlayerEntity::moveLeft();

}

std::vector<Pokemon *> PlayerEntity::getPokemons() const {
    return (this->pokemons);
}

void PlayerEntity::setPokemons(std::vector<Pokemon *> newList) {
    this->pokemons = newList;
}

void PlayerEntity::initPokemons() {
    this->pokemons.push_back(ListPokemon::GetInstance().GetPokemonByName("Bulbizarre"));
    this->pokemons.push_back(ListPokemon::GetInstance().GetPokemonByName("Salameche"));
    this->pokemons.push_back(ListPokemon::GetInstance().GetPokemonByName("Carapuce"));
    this->pokemons.push_back(ListPokemon::GetInstance().GetPokemonByName("Aspicot"));
    this->pokemons.push_back(ListPokemon::GetInstance().GetPokemonByName("Chenipan"));
    this->pokemons.at(0)->setXp(100);
    this->pokemons.at(1)->setXp(100);
    this->pokemons.at(2)->setXp(100);
    this->pokemons.at(3)->setXp(100);
    this->pokemons.at(4)->setXp(100);
}

void PlayerEntity::addPokemon(Pokemon* pokemon){
    this->pokemons.push_back(ListPokemon::GetInstance().GetPokemonByName(pokemon->getName()));
}

void PlayerEntity::changePokemon(int selector, Pokemon* pokemon){
    this->pokemons.erase(this->pokemons.begin()+selector);
    this->pokemons.insert(this->pokemons.begin()+selector, pokemon);
}

bool PlayerEntity::hasPokemonAlive() {
    std::vector<Pokemon *>::iterator ptr;

    ptr = this->pokemons.begin();
    while (ptr != this->pokemons.end())
    {
        if ((*ptr)->getHp() > 0){
            return true;
        }
        ++ptr;
    }
    return false;
}

Pokemon* PlayerEntity::getFirstPokemonAlive() {
    std::vector<Pokemon *>::iterator ptr;

    ptr = this->pokemons.begin();
    while (ptr != this->pokemons.end())
    {
        if ((*ptr)->getHp() > 0){
            return (*ptr);
        }
        ++ptr;
    }
    return NULL;
}

void PlayerEntity::setIsMoving() {
    if (this->isMoving == 15) {
        this->coord = this->getSpriteCoord(this->getDirection());
        this->isMoving = 0;
    }
    else {
        this->isMoving = this->isMoving +1;
    }
    if (this->isMoving != 0) {
        if ((this->isMoving % 2) == 0)
            this->coord = this->getSpriteCoordMoveFirst(this->getDirection());
        else
            this->coord = this->getSpriteCoordMoveSecond(this->getDirection());
    }
    this->move();
}

int PlayerEntity::getIsMoving() {
    return this->isMoving;
}

int PlayerEntity::turn(char key) {
    Map &map = Map::GetInstance();
    Game &game = Game::GetInstance();
    BuildingFactory &bf = BuildingFactory::getInstance();
    std::string direction;
    switch (key) {
        case ('Z'):
            direction = "N";
            break;
        case ('S'):
            direction = "S";
            break;
        case ('Q'):
            direction = "O";
            break;
        case ('D'):
            direction = "E";
            break;
        case ('P'):
            game.setBuilding(bf.Create("PokemonCenter"));
            break;
        default:
            break;
    }
    if (this->getDirection() != direction) {
        PlayerEntity::direction = direction;
        PlayerEntity::coord = PlayerEntity::getSpriteCoord(direction);
        return 1;
    }
    else
        return 0;
}

void PlayerEntity::healAllTeam(){
    std::vector<Pokemon *>::iterator ptr;

    ptr = this->pokemons.begin();
    while (ptr != this->pokemons.end())
    {
        (*ptr)->setHp((*ptr)->getHpMax());
        ++ptr;
    }
}

void PlayerEntity::TeamDied(){
    std::vector<Pokemon *>::iterator ptr;

    ptr = this->pokemons.begin();
    while (ptr != this->pokemons.end())
    {
        (*ptr)->setHp((*ptr)->getHpMax());
        (*ptr)->looseXp();
        ++ptr;
    }
}

void PlayerEntity::resetDied() {
    this->X = 160;
    this->Y = 160;
    this->direction = "S";
    this->coord = this->getSpriteCoord(this->direction);
    this->isMoving = 0;
}

void PlayerEntity::free() {
    std::vector<Pokemon *> m_list = PlayerEntity::getInstance().getPokemons();
    std::vector<Pokemon *>::iterator ptr;
    ptr = m_list.begin();
    while (ptr != m_list.end())
    {
        delete (*ptr);
        ++ptr;
    }
    delete PlayerEntity::getInstance().getBag();
    delete instance;
}


Bag* PlayerEntity::getBag() const{
    return (this->m_inventaire);
}

void PlayerEntity::setX(int X) {
    PlayerEntity::X = X;
}

void PlayerEntity::setY(int Y) {
    PlayerEntity::Y = Y;
}
