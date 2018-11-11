#ifndef CHARACTER_H
#define CHARACTER_H

#include "AbstractEntity.hh"
#include "../Manager/ResourceManager.hh"


class Character : public AbstractEntity, public sf::Drawable, public sf::Transformable
{
public:
    Character();
    virtual ~Character() = 0;

    void Draw();
    void Update();
    static const std::string name;
private:
    sf::VertexArray perso;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
