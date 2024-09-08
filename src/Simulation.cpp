#include "Simulation.h"
#include "Deadlock.h"

Simulation::Simulation(Window *qtWindow, Deadlock *deadlock, QObject *parent) : QObject(parent), qtWindow(qtWindow),
                                                                                deadlock(deadlock), currentTime(0) {

    connect(qtWindow, &Window::generateDeadlockRequest, this, &Simulation::createDeadlock);
    connect(deadlock, &Deadlock::setBankersEntry, qtWindow, &Window::updateTableStatus);

    connect(qtWindow, &Window::runBankersAlgorithmRequest, this, &Simulation::runBankersAlgorithm);
    connect(qtWindow, &Window::runInterruptProcessRequest, this, &Simulation::runInterruptProcess);
    connect(qtWindow, &Window::runAbortProcessRequest, this, &Simulation::runAbortProcess);
    connect(qtWindow, &Window::runAvoidanceStrategyRequest, this, &Simulation::runAvoidanceStrategy);
    connect(qtWindow, &Window::runProcessEventsRequest, this, &Simulation::startEventSchedulingSimulation);

    connect(qtWindow, &Window::runScheduleBankersAlgorithmRequest, this, &Simulation::triggerBankersAlgorithm);
    connect(qtWindow, &Window::runScheduleInterruptProcessRequest, this, &Simulation::triggerInterruptProcess);
    connect(qtWindow, &Window::runScheduleAbortProcessRequest, this, &Simulation::triggerAbortProcess);

    connect(&timer, &QTimer::timeout, this, &Simulation::processEvents);
    connect(&timer, &QTimer::timeout, this, &Simulation::updateTimerDisplay);
    timer.setInterval(1000);
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

void Simulation::runAbortProcess() {
    deadlock->runAbortProcess();
}

void Simulation::runAvoidanceStrategy() {
    deadlock->runAvoidanceStrategy();
}

void Simulation::triggerBankersAlgorithm() {
    std::string desc = "Run Bankers Algorithm";
    scheduleEvent(Event([this]() { deadlock->runBankersAlgorithm(); }, currentTime + 2, desc));
}

void Simulation::triggerInterruptProcess() {
    std::string desc = "Run Interrupt Process";
    scheduleEvent(Event([this]() { deadlock->runInterruptProcess(); }, currentTime + 3, desc));
}

void Simulation::triggerAbortProcess() {
    std::string desc = "Run Abort Process";
    scheduleEvent(Event([this]() { deadlock->runAbortProcess(); }, currentTime + 2, desc));

}

void Simulation::scheduleEvent(const Event &event) {
    std::cout << "Scheduling Event for " << event.executeTime << ": " << event.description << std::endl;
    eventQueue.addEvent(event);
}

void Simulation::updateTimerDisplay() {
    std::cout << "Current Simulation Time: " << currentTime << "s\n";
}

void Simulation::startEventSchedulingSimulation() {
    if (!timer.isActive()) {
        timer.start();
        std::cout << "Simulation started at time: " << currentTime << std::endl;
    }
}

void Simulation::processEvents() {
    while (!eventQueue.isEmpty() && eventQueue.top().executeTime <= currentTime) {
        Event nextEvent = eventQueue.top();
        eventQueue.pop();

        nextEvent.action();
        std::cout << "Executing event: " << nextEvent.description << " at simulation time " << currentTime << std::endl;

        updateTimerDisplay();
    }

    if (eventQueue.isEmpty()) {
        timer.stop();
        std::cout << "No more events to process. Simulation got paused." << std::endl;
    }

    if (timer.isActive()) {
        currentTime++;
    }
}

