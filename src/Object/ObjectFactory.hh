//
// Created by root on 4/26/17.
//

#ifndef POKEMON_OBJECTFACTORY_HH
#define POKEMON_OBJECTFACTORY_HH

#include "Object.hh"
#include "HealObject.hh"
#include "CatchObjects.hh"

class ObjectFactory {
public:
    ObjectFactory();
    ~ObjectFactory();
    static Object* Create(const std::string& str);
};


#endif //POKEMON_OBJECTFACTORY_HH
