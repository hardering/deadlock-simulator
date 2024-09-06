#include <QApplication>
#include "Window.h"
#include "Simulation.h"

// Include the test function
void testBasicFunctionality();

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Run the test function
    testBasicFunctionality();

    Window window;

    auto *simulation = new Simulation();
    auto *r1 = new Resource(1, 3);
    auto *r2 = new Resource(2, 3);
    auto *r3 = new Resource(3, 3);

    auto *p1 = new Process(1, simulation, {{r1, 0, 2},
                                           {r2, 1, 0},
                                           {r3, 2, 0}});

    auto *p2 = new Process(2, simulation, {{r1, 2, 0},
                                           {r2, 0, 1},
                                           {r3, 1, 1}});

    auto *p3 = new Process(3, simulation, {{r1, 2, 0},
                                           {r2, 1, 1},
                                           {r3, 0, 0}});

    QObject::connect(simulation, &Simulation::resourceAdded,
                     &window, &Window::handleResourceAdded);

    QObject::connect(simulation, &Simulation::processAdded,
                     &window, &Window::handleProcessAdded);

    simulation->addResource(r1);
    simulation->addResource(r2);
    simulation->addResource(r3);

    simulation->addProcess(p1);
    simulation->addProcess(p2);
    simulation->addProcess(p3);
    window.show();

    return QApplication::exec();
}