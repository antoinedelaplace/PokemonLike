//
// Created by Romain on 31/03/2017.
//

#ifndef POKEMON_LISTATTACK_HH
#define POKEMON_LISTATTACK_HH

#include <iostream>
#include <list>
#include <string>
#include "../Fight/Attack.hh"
#include <list>
#include <fstream>

class ListAttack {
public:
    static ListAttack& GetInstance();
    void Start();
    Attack*	GetAttackByName(std::string) const;
    static void free();
private:
    std::list<Attack *> listAttack;
    ListAttack();
    ~ListAttack();
    ListAttack& operator = (const ListAttack&);
    ListAttack (const ListAttack&){}
    static ListAttack *instance;
};


#endif //POKEMON_LISTATTACK_HH
