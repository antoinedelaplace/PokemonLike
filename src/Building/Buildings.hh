//
// Created by Benoît - Xavier HOUVET on 28/04/2017.
//

#ifndef SFMLDEMO_BUILDINGS_HH
#define SFMLDEMO_BUILDINGS_HH


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "../Pattern/IObserver.hh"

class Buildings : public IObserver, public sf::Drawable, public sf::Transformable {
public:
    Buildings();
    virtual ~Buildings() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual int isValidTile(int X, int Y) = 0;
    void Notify(char i)=0;
};


#endif //SFMLDEMO_BUILDINGS_HH
