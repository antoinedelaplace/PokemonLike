#ifndef POKEMON_OBJECT_HH
#define POKEMON_OBJECT_HH

#include "../Entity/AbstractEntity.hh"
#include "../Entity/Pokemon.hh"

class Object{
public:
    Object();
    virtual ~Object();
    virtual int Use(Pokemon* launcher, Pokemon* target);
    std::string getName() const;
    int getValueEffect() const;
    void setValueEffect(int);
    void setName(std::string);
private:
    int valueEffect;
    std::string name;
};


#endif //POKEMON_OBJECT_HH
