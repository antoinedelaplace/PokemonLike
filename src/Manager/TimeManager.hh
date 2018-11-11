//
// Created by Benoît - Xavier HOUVET on 09/03/2017.
//

#ifndef C_TIMEMANAGER_HH
#define C_TIMEMANAGER_HH

#include <chrono>
#include <iostream>

class TimeManager {
public:
    static TimeManager& GetInstance();
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> first;
    std::chrono::time_point<std::chrono::system_clock> second;
    void Start();
    void Update();
    unsigned int GetElapsedTime() const;
    unsigned int GetStartedTime() const;
    static void free();
private:
    static TimeManager* Instance;
    TimeManager& operator = (const TimeManager&);
    TimeManager();
    ~TimeManager();
};


#endif //C_TIMEMANAGER_HH
