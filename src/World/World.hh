//
// Created by Benoît - Xavier HOUVET on 28/04/2017.
//

#ifndef SFMLDEMO_WORLD_HH
#define SFMLDEMO_WORLD_HH

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "../Pattern/IObserver.hh"
#include "../Map/Map.hh"
#include "../Game.hh"

class World : public IObserver, public sf::Drawable, public sf::Transformable {
public:
    static World& getInstance();
    void Notify(char i);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    World();
    ~World();
    static World* instance;
};


#endif //SFMLDEMO_WORLD_HH
