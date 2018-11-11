//
// Created by Benoît - Xavier HOUVET on 09/03/2017.
//

#include "TimeManager.hh"

TimeManager* TimeManager::Instance= new TimeManager();

TimeManager::TimeManager() {
    this->start = std::chrono::system_clock::now();
    this->first = this->start;
    this->second = this->start;
}

TimeManager::~TimeManager() {
}

void TimeManager::Start() {
    this->start = std::chrono::system_clock::now();
    this->first = this->start;
    this->second = this->start;
}

void TimeManager::Update() {
    this->second = this->first;
    this->first = std::chrono::system_clock::now();
}

TimeManager& TimeManager::GetInstance() {
    return *Instance;
}

unsigned int TimeManager::GetElapsedTime() const {
    std::chrono::system_clock::duration duree;
    std::chrono::milliseconds millis;

    duree = (this->first.time_since_epoch() - this->second.time_since_epoch());
    millis = std::chrono::duration_cast<std::chrono::milliseconds> (duree);
    return (millis.count());
}

unsigned int TimeManager::GetStartedTime() const {
    std::chrono::system_clock::duration duree;
    std::chrono::milliseconds millis;

    duree = (this->first.time_since_epoch() - this->start.time_since_epoch());
    millis = std::chrono::duration_cast<std::chrono::milliseconds> (duree);
    return (millis.count());
}

void TimeManager::free() {
    delete Instance;
}
