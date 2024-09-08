#include "Event.h"

#include <utility>

Event::Event(std::function<void()> action, int executeTime, std::string desc)
        : action(action), executeTime(executeTime), description(std::move(desc)) {}

bool Event::operator<(const Event &other) const {
    return executeTime > other.executeTime;
}