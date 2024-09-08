#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#pragma once

using namespace std;

class Event {

public:
    int executeTime;
    function<void()> action;
    std::string description;

    Event(std::function<void()> action, int executeTime, std::string desc);

    bool operator<(const Event &other) const;
};