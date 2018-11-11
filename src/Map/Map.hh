#ifndef FIRST_MAP_HH
#define FIRST_MAP_HH

#include "../Manager/ResourceManager.hh"
#include "../Manager/LogManager.hh"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class Map : public sf::Drawable, public sf::Transformable
{
public:
    static Map& GetInstance();
    void load(sf::Vector2u tileSize, unsigned int width, unsigned int height);
    int isValidTile(int x, int y);
    int isFightTile(int x, int y);
    static void free();
private:
    static Map* instance;
    sf::VertexArray baseCalque;
    sf::VertexArray collisionCalque;
    Map();
    ~Map();
    unsigned int width;
    unsigned int height;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void loadCalque(sf::VertexArray &calque, std::vector<int> &tiles, std::string, sf::Vector2u tileSize);
    std::vector<int> basetiles;
    std::vector<int> collisiontiles;
};


#endif //FIRST_MAP_HH
