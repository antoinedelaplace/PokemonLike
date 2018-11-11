//
// Created by root on 4/26/17.
//

#include "HealObject.hh"

HealObject::HealObject(int val, std::string name) : Object() {
    this->setName(name);
    this->setValueEffect(val);
}

HealObject::~HealObject(){
}

int HealObject::Use(Pokemon* launcher, Pokemon* target){
    launcher->Heal(this->getValueEffect());
    return (-1);
}