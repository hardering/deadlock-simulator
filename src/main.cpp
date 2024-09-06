#include <QApplication>
#include "../qt/Window.h"
#include "../tests/BankersAlgorithmTest.h"
#include "../tests/DeadlockTest.h"
#include "../tests/DeadlockRecoveryTest.h"
#include "../tests/DeadlockAvoidanceTest.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Window window;
    window.show();

    DeadlockAvoidanceTest avoidanceTests;
    avoidanceTests.runAllTests();

    DeadlockRecoveryTest recoveryTests;
    recoveryTests.runAllTests();

    BankersAlgorithmTest bankersTests;
    bankersTests.runAllTests();

    QApplication::exec();
}
