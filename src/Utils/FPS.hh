//
// Created by Benoît - Xavier HOUVET on 26/04/2017.
//

#ifndef SFMLDEMO_FPS_HH
#define SFMLDEMO_FPS_HH


#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "../Pattern/IObserver.hh"
#include "../Game.hh"

class FPS : public sf::Drawable, public sf::Transformable, public IObserver{
public:
    static FPS& getInstance();
    void Notify(char i) override;
    static void free();
private:
    double frame;
public:
    double getFrame() const;

    void setFrame(double frame);

private:
    static FPS* instance;
    FPS();
    ~FPS();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif //SFMLDEMO_FPS_HH
