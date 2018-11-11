//
// Created by root on 4/26/17.
//

#ifndef POKEMON_BAG_HH
#define POKEMON_BAG_HH

#include "../List/ListObjects.hh"
#include <map>

class Bag {
public:
    Bag();
    ~Bag();
    void addItem(Object* obj, int quantite);
    void removeItem(Object* obj, int quantite);
    Object* getItem(int index);
    void setInventaire(std::map<Object *, int >);
    const std::map<Object *, int> &getInventaire() const;

private:
    std::map<Object *, int > inventaire;
};


#endif //POKEMON_BAG_HH
