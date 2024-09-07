#ifndef DEADLOCK_SIMULATOR_SIMULATION_H
#define DEADLOCK_SIMULATOR_SIMULATION_H

#include <QObject>
#include "../qt/Window.h"
#include "Deadlock.h"

class Simulation : public QObject {
Q_OBJECT

private:
    Window *qtWindow;
    Deadlock *deadlock;

public:
    explicit Simulation(Window *qtWindow, Deadlock *deadlock, QObject *parent = nullptr);

    void start();
};

#endif
