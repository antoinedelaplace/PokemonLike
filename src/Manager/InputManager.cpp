//
// Created by Benoît - Xavier HOUVET on 05/04/2017.
//

#include "InputManager.hh"

InputManager* InputManager::instance = new InputManager();

InputManager::InputManager() : IObservable() {}

InputManager::~InputManager() {

}
InputManager& InputManager::getInstance() {
    return (*instance);
}

void InputManager::move(sf::Event event) {
    if (event.type == sf::Event::JoystickButtonPressed)
    {
        if (event.joystickButton.button == 14) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('E');
            }
        }

        if (event.joystickButton.button == 13) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('R');
            }
        }

        if (event.joystickButton.button == 7) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('Q');
            }
        }

        if (event.joystickButton.button == 6) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('S');
            }
        }

        if (event.joystickButton.button == 4) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('Z');
            }
        }

        if (event.joystickButton.button == 5) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('D');
            }
        }

        if (event.joystickButton.button == 12) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('T');
            }
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::S) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('S');
            }
        }

        if (event.key.code == sf::Keyboard::Z) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('Z');
            }
        }

        if (event.key.code == sf::Keyboard::Q) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('Q');
            }
        }

        if (event.key.code == sf::Keyboard::D) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('D');
            }
        }

        if (event.key.code == sf::Keyboard::R) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('R');
            }
        }

        if (event.key.code == sf::Keyboard::Space) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('E');
            }
        }

        if (event.key.code == sf::Keyboard::T) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('T');
            }
        }

        if (event.key.code == sf::Keyboard::P) {
            for (std::list<IObserver *>::iterator it = this->observers.begin(); it != this->observers.end(); it++) {
                (*it)->Notify('P');
            }
        }
    }
}

void InputManager::AddObserver(IObserver *obs) {
    this->observers.push_back(obs);
}

void InputManager::RemoveObserver(IObserver *obs) {
    this->observers.remove(obs);
}

void InputManager::free() {
    delete instance;
}
