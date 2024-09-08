#include "Simulation.h"
#include "Deadlock.h"

Simulation::Simulation(Window *qtWindow, Deadlock *deadlock, QObject *parent) : QObject(parent), qtWindow(qtWindow),
                                                                                deadlock(deadlock) {
    connect(qtWindow, &Window::generateDeadlockRequest, this, &Simulation::createDeadlock);
    connect(qtWindow, &Window::runBankersAlgorithmRequest, this, &Simulation::runBankersAlgorithm);
    connect(qtWindow, &Window::runInterruptProcessRequest, this, &Simulation::runInterruptProcess);
    connect(deadlock, &Deadlock::setBankersEntry, qtWindow, &Window::updateTableStatus);
}

void Simulation::createDeadlock() {
    deadlock->createDeadlock();
}

void Simulation::runBankersAlgorithm() {
    deadlock->runBankersAlgorithm();
}

void Simulation::runInterruptProcess() {
    deadlock->runInterruptProcess();
}
