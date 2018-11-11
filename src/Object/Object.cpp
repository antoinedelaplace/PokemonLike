#include "Object.hh"

Object::Object() {
}

Object::~Object(){
}

int Object::Use(Pokemon* launcher, Pokemon* target){
    return (-1);
}

void Object::setName(std::string name){
    this->name = name;
}

void Object::setValueEffect(int val) {
    this->valueEffect = val;
}

int Object::getValueEffect() const {
    return valueEffect;
}

std::string Object::getName() const {
    return name;
}

