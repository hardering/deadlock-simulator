#include "EventQueue.h"

void EventQueue::addEvent(const Event &e) {
    events.push(e);
}

void EventQueue::processEvents() {
    while (!events.empty()) {
        Event nextEvent = events.top();
        if (nextEvent.executeTime <= currentTime) {
            std::cout << "Executing Event at " << currentTime << ": " << nextEvent.description << std::endl;
            events.pop();
            nextEvent.action();
        } else {
            break;
        }
    }
}

bool EventQueue::isEmpty() const {
    return events.empty();
}

Event EventQueue::top() const {
    return events.top();
}

void EventQueue::pop() {
    events.pop();
}