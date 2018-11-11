//
// Created by Benoît - Xavier HOUVET on 28/04/2017.
//

#ifndef SFMLDEMO_POKEMONCENTER_HH
#define SFMLDEMO_POKEMONCENTER_HH


#include "Buildings.hh"
#include <vector>
#include "../Manager/ResourceManager.hh"
#include "../Game.hh"
#include <SFML/Graphics/Text.hpp>

class PokemonCenter : public Buildings {
public:
    PokemonCenter();
    void Notify(char i) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    int isValidTile(int X, int Y) override;

private:
    void drawBlackColorBackground(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const;
    std::vector<int> collisiontiles;
    int X = 304;
    int Y = 560;
};


#endif //SFMLDEMO_POKEMONCENTER_HH
