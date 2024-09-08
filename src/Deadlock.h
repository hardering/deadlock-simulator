#pragma once

#import <QString>
#include <QTableWidget>
#include "Process.h"
#include "Resource.h"
#include "DeadlockRecovery.h"
#include "../qt/Window.h"
#include "DeadlockAvoidance.h"

/**
 * @class Deadlock
 * @brief Die Klasse Deadlock verwaltet die Ressourcen und Prozesse und bietet Methoden zur Erkennung, Vermeidung und Behebung von Deadlocks in einem System.
 */
class Deadlock : public QObject {
Q_OBJECT

private:
    std::vector<Resource> resources; /**< Liste der verfügbaren Ressourcen im System. */
    std::vector<Process> processes;  /**< Liste der laufenden Prozesse im System. */
    Window *window;                  /**< Zeiger auf das Qt-Fenster zur Darstellung der Simulation. */
    std::vector<int> request_01, request_02, request_03, request_04; /**< Beispielhafte Ressourcenzuweisungen für Prozesse. */
    std::vector<std::vector<int>> requests; /**< Sammlung von Ressourcenzuweisungen für verschiedene Prozesse. */
    DeadlockDetector *deadlockDetector; /**< Zeiger auf den Deadlock-Detektor, der zur Deadlockerkennung verwendet wird. */
    DeadlockRecovery *deadlockRecovery; /**< Zeiger auf die Klasse zur Deadlock-Behebung. */
    DeadlockAvoidance *deadlockAvoidance; /**< Zeiger auf die Klasse zur Deadlock-Vermeidung. */
    std::string status; /**< Status des Systems (z.B. sicher, unsicher, Deadlock). */

public:

    /**
     * @brief Konstruktor, der das Deadlock-Objekt initialisiert und ein Fenster zur Anzeige verwendet.
     * @param window Zeiger auf das Fenster, das die UI-Komponente repräsentiert.
     */
    Deadlock(Window *window);

    /**
     * @brief Initialisiert die Ressourcen und Prozesse für die Deadlock-Simulation.
     */
    void initializeResourcesAndProcesses();

    /**
     * @brief Löscht alle gespeicherten Ressourcen und Prozesse.
     */
    void clear();

    /**
     * @brief Wandelt einen Vektor von Ganzzahlen in einen QString um.
     * @param vector Der Vektor, der umgewandelt werden soll.
     * @return Ein QString, der die Werte des Vektors darstellt.
     */
    QString vectorToQString(const std::vector<int> &vector);

    /**
     * @brief Aktualisiert die UI-Tabelle mit den aktuellen Werten der Ressourcen und Prozesse.
     */
    void updateTable();

    /**
     * @brief Gibt eine bestimmte Ressourcenzuweisung für einen Prozess zurück.
     * @param n Die Nummer des Prozesses (z.B. 1 für request_01).
     * @return Ein Vektor mit der Ressourcenzuweisung für den angegebenen Prozess.
     */
    std::vector<int> getRequest(int n);

    /**
     * @brief Gibt den aktuellen Systemzustand zurück (z.B. sicher, unsicher, Deadlock).
     * @return Ein QString, der den Zustand des Systems beschreibt.
     */
    QString getState();

public slots:

    /**
     * @brief Signal, damit die Simulation die Funktion im Button ausführen kann. Erzeugt eine Deadlock-Situation für die Simulation.
     */
    void createDeadlock();

    /**
     * @brief Signal, damit die Simulation die Funktion im Button ausführen kann. Führt den Banker's Algorithmus zur Deadlock-Vermeidung aus.
     */
    void runBankersAlgorithm();

    /**
     * @brief Signal, damit die Simulation die Funktion im Button ausführen kann. Unterbricht einen Prozess, um Ressourcen freizugeben.
     */
    void runInterruptProcess();

    /**
     * @brief Signal, damit die Simulation die Funktion im Button ausführen kann. Bricht einen Prozess ab, um Ressourcen freizugeben und einen Deadlock zu lösen.
     */
    void runAbortProcess();

    /**
     * @brief Signal, damit die Simulation die Funktion im Button ausführen kann. Führt eine Vermeidungsstrategie zur Deadlock-Prävention durch.
     */
    void runAvoidanceStrategy();

signals:

    /**
     * @brief Signal, um die Daten in einer Tabelle im UI zu setzen.
     * @param table Zeiger auf das QTableWidget, in das die Daten gesetzt werden.
     * @param data Die Liste der Daten, die in die Tabelle eingetragen werden sollen.
     */
    void setTableData(QTableWidget *table, const QList<QString> &data);

    /**
     * @brief Signal, um den Status eines Eintrags im Banker's Algorithmus anzuzeigen.
     * @param processId Die ID des Prozesses.
     * @param status Der Status des Prozesses (true = erfolgreich, false = fehlgeschlagen).
     */
    void setBankersEntry(int processId, bool status);
};
