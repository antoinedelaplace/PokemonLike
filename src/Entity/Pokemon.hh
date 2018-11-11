//
// Created by Romain on 31/03/2017.
//

#ifndef POKEMON_POKEMON_HH
#define POKEMON_POKEMON_HH

#include "../Fight/Attack.hh"
#include <string>
#include <iostream>
#include <vector>

class Pokemon {
public:
    Pokemon();
    Pokemon(Pokemon* pokemon);//std::string name, int atk, int def, int xp, int xpmax, int hp, int hpMax, const int coordFace[4], const int coordDos[4]);
    void setName(std::string name);
    void setAtk(int atk);
    void setDef(int def);
    void addCoordFace(int coord, int index);
    void addCoordDos(int coord, int index);
    virtual ~Pokemon();
    int getLevel() const;
    int getHp() const;
    int getHpMax() const;
    int getXp() const;
    int getXpMax() const;
    int getAtk() const;
    int getDef() const;
    const std::string &getName() const;
    const int *getCoordFace() const;
    const int *getCoordDos() const;
    void hit(Attack* atk, Pokemon* cible);
    void setXp(int xp);
    void setXpMax(int xp);
    void setHp(int hp);
    void setHpMax(int hp);
    void giveXp(int xp);
    void Heal(int val);
    void addAttack(Attack* atk);
    Attack* getRandomAttack();
    std::vector<Attack *> getAttacks() const;
    void looseXp();
    float getPourcentNextLvl() const;
    int getXpForNextLevel() const;
    int getXpInLevel() const;
    void levelUp();
    void setXpLevelOne(int val);
    int getXpLevelOne() const;
    int getXpLevel(int level) const;
private:
    std::string name;
    int xp;
    int xpLvlOne;
    int xpmax;
    int hp;
    int hpMax;
    int atk;
    int def;
    int coordFace[4];
    int coordDos[4];
    std::vector<Attack *> Attacks;
};


#endif //POKEMON_POKEMON_HH
