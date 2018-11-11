//
// Created by Benoît - Xavier HOUVET on 26/04/2017.
//

#include "FPS.hh"

FPS* FPS::instance = new FPS();

FPS& FPS::getInstance() {
    return *instance;
}

void FPS::Notify(char i) {
    if (i == 'T') {
        Game &game = Game::GetInstance();
        game.isFPS();
    }
}

FPS::~FPS() {

}

FPS::FPS() {}

void FPS::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    ResourceManager &rm = ResourceManager::GetInstance();
    TimeManager &tm = TimeManager::GetInstance();
    sf::Text text;
    text.setFont(rm.getMainFont());
    if (tm.GetStartedTime() >= 500 || getFrame() == 0.0) {
        double fps = 1000.00 / tm.GetElapsedTime();
        FPS::getInstance().setFrame(fps);
    }
    text.setString(std::to_string(getFrame()));
    text.setColor(sf::Color::Black);
    text.setCharacterSize(24);
    target.draw(text);
}

void FPS::free() {
    delete instance;
}

double FPS::getFrame() const {
    return frame;
}

void FPS::setFrame(double frame) {
    FPS::frame = frame;
}
