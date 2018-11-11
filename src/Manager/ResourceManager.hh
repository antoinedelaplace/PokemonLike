#ifndef FIRST_RESOURCEMANAGER_HH
#define FIRST_RESOURCEMANAGER_HH

#include "LogManager.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager {
public:
    static ResourceManager& GetInstance();
    int load();
    const sf::Texture &getMainTileset() const;
    sf::Music &getMainMusic();
    const sf::Texture &getPokemonsTileset() const;
    const sf::Texture &getBackgroundsTileset() const;
    const sf::Texture &getBattleMenuTileset() const;
    const sf::Font &getMainFont() const;
    const sf::Texture &getPersoTileset() const;
    const sf::Texture &getBuildingTileset() const;
    static void free();

private:
    static ResourceManager* instance;
    ResourceManager();
    ~ResourceManager();
    sf::Texture mainTileset;
    sf::Texture pokemonsTileset;
    sf::Texture persoTileset;
    sf::Texture backgroundsTileset;
    sf::Texture battleMenuTileset;
    sf::Texture buildingTileset;
    sf::Music mainMusic;
    sf::Font mainFont;
};


#endif //FIRST_RESOURCEMANAGER_HH
