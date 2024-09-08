#ifndef DEADLOCK_SIMULATOR_SIMULATION_H
#define DEADLOCK_SIMULATOR_SIMULATION_H

#include <QObject>
#include <QTimer>
#include "../qt/Window.h"
#include "Deadlock.h"
#include "Event.h"
#include "EventQueue.h"

class Simulation : public QObject {
Q_OBJECT

private:
    Window *qtWindow;
    Deadlock *deadlock;

    int currentTime = 0;
    QTimer timer;
    EventQueue eventQueue;

public:
    explicit Simulation(Window *qtWindow, Deadlock *deadlock, QObject *parent = nullptr);

    void createDeadlock();

    void runBankersAlgorithm();

    void runInterruptProcess();

    void runAbortProcess();

    void triggerBankersAlgorithm();

    void triggerAbortProcess();

    void triggerInterruptProcess();

    void processEvents();

    void scheduleEvent(const Event &event);

    void updateTimerDisplay();

    void startSimulation();


};

#endif
