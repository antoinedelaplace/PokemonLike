//
// Created by root on 4/26/17.
//

#ifndef POKEMON_HEALOBJECT_HH
#define POKEMON_HEALOBJECT_HH

#include "../Entity/AbstractEntity.hh"
#include "Object.hh"

class HealObject : public Object {
public:
    HealObject(int, std::string);
    virtual ~HealObject();
    int Use(Pokemon* launcher, Pokemon* target);
};


#endif //POKEMON_HEALOBJECT_HH
