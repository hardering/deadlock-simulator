#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "Event.h"

using namespace std;

class EventQueue {
private:
    std::priority_queue<Event> events;
    int currentTime = 0;

public:
    void addEvent(const Event &e);

    void processEvents();

    bool isEmpty() const;

    Event top() const;

    void pop();
};