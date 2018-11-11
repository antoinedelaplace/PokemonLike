//
// Created by Benoît - Xavier HOUVET on 28/04/2017.
//

#ifndef SFMLDEMO_BUILDINGFACTORY_HH
#define SFMLDEMO_BUILDINGFACTORY_HH


#include <string>
#include "Buildings.hh"
#include "PokemonCenter.hh"

class BuildingFactory {
public:
    static BuildingFactory& getInstance();
    static Buildings* Create(const std::string&);
private:
    BuildingFactory();
    ~BuildingFactory();
    static BuildingFactory* instance;

};


#endif //SFMLDEMO_BUILDINGFACTORY_HH
