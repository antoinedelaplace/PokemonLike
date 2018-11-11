//
// Created by Romain on 31/03/2017.
//

#include "Attack.hh"

Attack::Attack() {
}

Attack::~Attack(){
}

Attack::Attack(std::string name, int dmg){
    this->setName(name);
    this->setDmg(dmg);
}

std::string Attack::GetName() const {
    return (this->name);
}

int Attack::GetDmg() const{
    return (this->dmg);
}

void Attack::setName(std::string name){
    this->name = name;
}

void Attack::setDmg(int dmg){
    this->dmg = dmg;
}

int Attack::getDmg() const {
    return dmg;
}

