//
// Created by root on 4/26/17.
//

#include "Bag.hh"

Bag::Bag(){
    ListObjects &lo = ListObjects::GetInstance();

    this->addItem(lo.GetObjectByName("Potion"), 5);
    this->addItem(lo.GetObjectByName("Pokeball"), 5);
    this->addItem(lo.GetObjectByName("Superball"), 5);
}

Bag::~Bag() {}

void Bag::addItem(Object* obj, int quantite) {
    std::map< Object*, int >::iterator ptr;
    bool hasObject = false;

    ptr = this->inventaire.begin();
    while (ptr != this->inventaire.end())
    {
        if(obj == std::get<0>((*ptr))){
            (*ptr).second += quantite;
            hasObject = true;
        }
        ++ptr;
    }
    if (!hasObject)
        this->inventaire.insert(std::make_pair(obj, quantite));
}

void Bag::removeItem(Object* obj, int quantite) {
    std::map< Object*, int >::iterator ptr;
    bool hasObject = false;

    ptr = this->inventaire.begin();
    while (ptr != this->inventaire.end())
    {
        if(obj == std::get<0>((*ptr))){
            (*ptr).second -= quantite;
            if ((*ptr).second < 0)
                this->inventaire.erase((*ptr).first);
            hasObject = true;
        }
        ++ptr;
    }
    if (!hasObject)
        std::cout << "Erreur, vous avec utilisé une quantité d'objet que vous n'êtes pas sensé avoir !" << std::endl;
}

Object* Bag::getItem(int index){
    std::map< Object*, int >::iterator ptr;

    ptr = this->inventaire.begin();
    for(int i = 0; i < index; i++)
        ++ptr;
    return ((*ptr).first);
}



void Bag::setInventaire(std::map<Object *, int > inv){
    this->inventaire = inv;
}

const std::map<Object *, int> &Bag::getInventaire() const {
    return inventaire;
}
