//
// Created by root on 4/26/17.
//

#ifndef POKEMON_LISTOBJECTS_HH
#define POKEMON_LISTOBJECTS_HH

#include <iostream>
#include <list>
#include <string>
#include "../Object/Object.hh"
#include "../Object/ObjectFactory.hh"
#include <fstream>
#include <ctime>

class ListObjects {
public:
    static ListObjects& GetInstance();
    Object*	GetObjectByName(std::string) const;
    Object* GetObjectRandom() const;
    static void free();
private:
    std::list<Object *> listObject;
    ListObjects();
    ~ListObjects();
    ListObjects& operator = (const ListObjects&);
    ListObjects (const ListObjects&){}
    static ListObjects* instance;
};


#endif //POKEMON_LISTOBJECTS_HH
