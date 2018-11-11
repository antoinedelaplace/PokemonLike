//
// Created by Romain on 31/03/2017.
//

#ifndef POKEMON_LISTPOKEMON_HH
#define POKEMON_LISTPOKEMON_HH

#include <iostream>
#include <list>
#include <string>
#include "../Entity/Pokemon.hh"
#include "ListAttack.hh"
#include <list>
#include <fstream>
#include <cstdlib>
#include <ctime>

class ListPokemon {
public:
    static ListPokemon& GetInstance();
    void Start();
    Pokemon*	GetPokemonByName(std::string) const;
    Pokemon*    GetPokemonRandom() const ;
    static void free();
private:
    std::list<Pokemon *> listPokemon;
    ListPokemon();
    ~ListPokemon();
    ListPokemon& operator = (const ListPokemon&);
    ListPokemon (const ListPokemon&){}
    static ListPokemon* instance;
};


#endif //POKEMON_LISTPOKEMON_HH
