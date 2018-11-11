//
// Created by Benoît - Xavier HOUVET on 28/04/2017.
//

#include "BuildingFactory.hh"

BuildingFactory* BuildingFactory::instance = new BuildingFactory();

BuildingFactory& BuildingFactory::getInstance() {
    return *instance;
}

BuildingFactory::BuildingFactory() {}

BuildingFactory::~BuildingFactory() {

}

Buildings *BuildingFactory::Create(const std::string& str) {
    if (str.compare("PokemonCenter") == 0) {
        PokemonCenter* PC = new PokemonCenter();
        return (PC);
    }

}



