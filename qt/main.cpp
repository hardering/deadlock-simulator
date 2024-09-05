#include <QApplication>
#include "Window.h"
#include "Simulation.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Window window;
    auto *simulation = new Simulation(&window);

    simulation->initializeProcessWithResources();

    window.show();

    return QApplication::exec();
}
