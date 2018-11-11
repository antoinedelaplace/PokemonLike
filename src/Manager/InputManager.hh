//
// Created by Benoît - Xavier HOUVET on 05/04/2017.
//

#ifndef SFMLDEMO_INPUTMANAGER_HH
#define SFMLDEMO_INPUTMANAGER_HH


#include "../Pattern/IObservable.hh"
#include <iostream>
#include <SFML/Window/Event.hpp>

#include "../Entity/PlayerEntity.hh"

class InputManager : public IObservable {
public:
    static InputManager &getInstance();
    void move(sf::Event);
    virtual void AddObserver(IObserver *obs);
    virtual void RemoveObserver(IObserver *obs);
    static void free();
private:
    static InputManager* instance;
    InputManager();
    virtual ~InputManager();
};


#endif //SFMLDEMO_INPUTMANAGER_HH
