//
// Created by root on 4/26/17.
//

#include "ObjectFactory.hh"

ObjectFactory::ObjectFactory(){
}

ObjectFactory::~ObjectFactory(){
}

Object* ObjectFactory::Create(const std::string& str){
    if (str.compare("Potion") == 0)
    {
        HealObject* H = new HealObject(20, str);
        return (H);
    }
    else if (str.compare("SuperPotion") == 0)
    {
        HealObject* C = new HealObject(50, str);
        return (C);
    }
    else if (str.compare("HyperPotion") == 0)
    {
        HealObject* C = new HealObject(100, str);
        return (C);
    }
    else if (str.compare("Pokeball") == 0)
    {
        CatchObjects* C = new CatchObjects(20, str);
        return (C);
    }
    else if (str.compare("Superball") == 0)
    {
        CatchObjects* C = new CatchObjects(40, str);
        return (C);
    }
    else if (str.compare("Hyperball") == 0)
    {
        CatchObjects* C = new CatchObjects(70, str);
        return (C);
    }
    else
        return (NULL);
}