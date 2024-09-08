#include <QApplication>
#include "../qt/Window.h"
#include "../tests/BankersAlgorithmTest.h"
#include "../tests/DeadlockTest.h"
#include "../tests/DeadlockRecoveryTest.h"
#include "../tests/DeadlockAvoidanceTest.h"
#include "Deadlock.h"
#include "Simulation.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Window window;
    auto *deadlock = new Deadlock(&window);
    auto *simulation = new Simulation(&window, deadlock);

/*    DeadlockAvoidanceTest avoidanceTests;
    avoidanceTests.runAllTests();

    DeadlockRecoveryTest recoveryTests;
    recoveryTests.runAllTests();

    BankersAlgorithmTest bankersTests;
    bankersTests.runAllTests();*/

    window.show();
    QApplication::exec();
}
