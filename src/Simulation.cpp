#include "Simulation.h"
#include "Deadlock.h"

Simulation::Simulation(Window *qtWindow, Deadlock *deadlock, QObject *parent) : QObject(parent), qtWindow(qtWindow),
                                                                                deadlock(deadlock) {
    connect(qtWindow, &Window::generateDeadlockRequest, this, &Simulation::createDeadlock);
}

void Simulation::createDeadlock() {
    deadlock->createDeadlock();
}
