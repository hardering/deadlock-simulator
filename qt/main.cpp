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
    auto *simulation = new Simulation(&window);
    window.show();

    return QApplication::exec();
}