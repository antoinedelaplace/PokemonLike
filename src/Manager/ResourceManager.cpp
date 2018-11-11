#include "ResourceManager.hh"

ResourceManager* ResourceManager::instance = new ResourceManager();

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

ResourceManager& ResourceManager::GetInstance() {
    return (*instance);
}

int ResourceManager::load() {
    if (!mainTileset.loadFromFile("houvet_b/resources/tileset/tileset-shinygold.png")) {
        LogManager::error_logs("Le chargement du tileset de la map a échoué");
        return (-1);
    }
    if (!persoTileset.loadFromFile("houvet_b/resources/tileset/perso.png")) {
        LogManager::error_logs("Le chargement du tileset du personnage a échoué");
        return (-1);
    }
    if (!pokemonsTileset.loadFromFile("houvet_b/resources/tileset/pokemons.png")) {
        LogManager::error_logs("Le chargement du tileset des pokemons a échoué");
        return (-1);
    }
    if (!backgroundsTileset.loadFromFile("houvet_b/resources/tileset/backgrounds.png")) {
        LogManager::error_logs("Le chargement du tileset des backgrounds a échoué");
        return (-1);
    }
    if (!battleMenuTileset.loadFromFile("houvet_b/resources/tileset/battle-menu.png")) {
        LogManager::error_logs("Le chargement du tileset des menus en combat a échoué");
        return (-1);
    }
    if (!buildingTileset.loadFromFile("houvet_b/resources/tileset/background-building.png")) {
        LogManager::error_logs("Le chargement du tileset des background des batiments a échoué");
        return (-1);
    }
    if(!mainMusic.openFromFile("houvet_b/resources/music/101-opening.wav")) {
        LogManager::error_logs("Le chargement de la musique a échoué");
        return (-1);
    }
    if (!mainFont.loadFromFile("houvet_b/resources/fonts/Banbury.otf"))
    {
        LogManager::error_logs("Le chargement de la police a échoué");
        return (-1);
    }
    return (1);
}

const sf::Texture &ResourceManager::getMainTileset() const {
    return (mainTileset);
}

sf::Music& ResourceManager::getMainMusic() {
    return (mainMusic);
}

const sf::Texture& ResourceManager::getPokemonsTileset() const {
    return (pokemonsTileset);
}

const sf::Texture &ResourceManager::getBackgroundsTileset() const {
    return (backgroundsTileset);
}

const sf::Texture &ResourceManager::getBattleMenuTileset() const {
    return (battleMenuTileset);
}

const sf::Font &ResourceManager::getMainFont() const {
    return (mainFont);
}

const sf::Texture &ResourceManager::getPersoTileset() const {
    return persoTileset;
}

void ResourceManager::free() {
    delete instance;
}

const sf::Texture &ResourceManager::getBuildingTileset() const {
    return buildingTileset;
}
