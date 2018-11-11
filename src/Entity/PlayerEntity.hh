//
// Created by Benoît - Xavier HOUVET on 30/03/2017.
//

#ifndef SFMLDEMO_PLAYERENTITY_HH
#define SFMLDEMO_PLAYERENTITY_HH

#include "AbstractEntity.hh"
#include "Character.hh"
#include "Pokemon.hh"
#include "../Pattern/IObserver.hh"
#include "../Object/Bag.hh"

class PlayerEntity : public Character {
public:
    static PlayerEntity& getInstance();
    int getX() const;
    int getY() const;
    const std::vector<int> &getCoord() const;
    void setCoord(const std::vector<int> &coord);
    std::string getDirection();
    void setDirection(std::string direction);
    std::vector<int> getSpriteCoord(std::string);
    std::vector<int> getSpriteCoordMoveFirst(std::string);
    std::vector<int> getSpriteCoordMoveSecond(std::string);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void move();
    std::vector<Pokemon *> getPokemons() const;
    void setPokemons(std::vector<Pokemon *>);
    void initPokemons();
    bool hasPokemonAlive();
    Pokemon* getFirstPokemonAlive();
    void setIsMoving();
    int getIsMoving();
    void TeamDied();
    void resetDied();
    static void free();
    Bag* getBag() const;
    void healAllTeam();
    void addPokemon(Pokemon* pokemon);
    void changePokemon(int selector, Pokemon* pokemon);
    int turn(char);
    void setX(int X);
    void setY(int Y);

private:
    static PlayerEntity* instance;
    PlayerEntity();
    ~PlayerEntity();
    int X;
    int Y;
    std::vector<int> coord;
    std::string direction;
    std::vector<Pokemon *> pokemons;
    int isMoving;
    Bag* m_inventaire;
};


#endif //SFMLDEMO_PLAYERENTITY_HH
