//
// Created by Romain on 31/03/2017.
//

#ifndef POKEMON_ATTACK_HH
#define POKEMON_ATTACK_HH

#include <string>

class Attack {
public:
    Attack();
    Attack(std::string, int);
    std::string GetName() const;
    int GetDmg() const;
    void setName(std::string name);
    void setDmg(int atk);
    virtual ~Attack();
    int getDmg() const;
private:
    std::string name;
    int dmg;
    //TODO : Enumerateur types + Ajout de faiblesses/critique
};

#endif //POKEMON_ATTACK_HH