#ifndef ABSTRACT_ENTITY_H
#define ABSTRACT_ENTITY_H

#include <string>
#include <iostream>

class AbstractEntity
{
public:
    AbstractEntity();
    virtual ~AbstractEntity() = 0;

    virtual void Draw() = 0;
    virtual void Update() = 0;
};

#endif
