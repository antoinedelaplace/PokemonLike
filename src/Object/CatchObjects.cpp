//
// Created by root on 4/26/17.
//

#include "CatchObjects.hh"
#include "../Entity/PlayerEntity.hh"


CatchObjects::CatchObjects(int val, std::string name) : Object() {
    this->setName(name);
    this->setValueEffect(val);
}

CatchObjects::~CatchObjects(){
}

int CatchObjects::Use(Pokemon* launcher, Pokemon* target){
    std::cout << "Use CatchObject   " << this->getName() << std::endl;
    int random = 0;
    srand(time(NULL));
    random = rand()%100;
    if(random >= 30){
        //Pokemon catch
        PlayerEntity &pm = PlayerEntity::getInstance();
        return (1);
    }
    return (0);
}