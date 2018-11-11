//
// Created by root on 4/26/17.
//

#ifndef POKEMON_CATCHOBJECTS_HH
#define POKEMON_CATCHOBJECTS_HH

#include "Object.hh"

class CatchObjects : public Object {
public:
    CatchObjects(int, std::string);
    virtual ~CatchObjects();
    int Use(Pokemon* launcher, Pokemon* target);
};


#endif //POKEMON_CATCHOBJECTS_HH
