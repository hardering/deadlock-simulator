#ifndef DEADLOCK_SIMULATOR_SIMULATION_H
#define DEADLOCK_SIMULATOR_SIMULATION_H

/**
 * @class Simulation
 * @brief Diese Klasse simuliert Deadlock-Szenarien und integriert sich in ein Qt-Fenster zur Anzeige.
 */

#include <QObject>
#include <QTimer>
#include "../qt/Window.h"
#include "Deadlock.h"
#include "Event.h"
#include "EventQueue.h"

class Simulation : public QObject {
Q_OBJECT

private:
    Window *qtWindow;                       /**< Zeiger auf das Qt-Fenster, das für die UI-Anzeige verwendet wird */
    Deadlock *deadlock;                     /**< Zeiger auf das Deadlock-Objekt, das Deadlock-Situationen behandelt */
    std::vector<Resource> resources;        /**< Vektor, der die Ressourcen im System speichert */
    std::vector<Process> processes;         /**< Vektor, der die Prozesse im System speichert */

    int currentTime = 0;                    /**< Verfolgt die aktuelle Simulationszeit */
    QTimer timer;                           /**< Qt-Timer, um Ereignisse in der Simulation zeitlich zu steuern */
    EventQueue eventQueue;                  /**< Ereigniswarteschlange zur Verwaltung von simulierten Ereignissen */

public:
/**
 * @brief Konstruktor der Simulation-Klasse.
 * @param qtWindow Zeiger auf das Qt-Fenster.
 * @param deadlock Zeiger auf das Deadlock-Objekt.
 * @param parent Zeiger auf das Eltern-Objekt von Qt-Objekt.
 **/
    explicit Simulation(Window *qtWindow, Deadlock *deadlock, QObject *parent = nullptr);

    /**
    * @brief Erstellt eine Deadlock-Situation, um diese zu simulieren.
    */
    void createDeadlock();

    /**
    * @brief Führt den Banker's-Algorithmus aus.
    */
    void runBankersAlgorithm();

    /**
     * @brief Beendet einen Prozess, um den Deadlock zu unterbrechen.
     */
    void runInterruptProcess();

    /**
     * @brief Bricht einen Prozess ab, um den Deadlock zu lösen.
     */
    void runAbortProcess();

    /**
     * @brief Führt eine Vermeidungsstrategie zur Deadlock-Prävention durch.
     */
    void runAvoidanceStrategy();

    /**
     * @brief Löst den Banker's-Algorithmus aus. Wird für den Button verwendet, um das Event zu schedulen.
     */
    void triggerBankersAlgorithm();

    /**
     * @brief Löst den Abbruch eines Prozesses aus. Wird für den Button verwendet, um das Event zu schedulen.
     */
    void triggerAbortProcess();

    /**
     * @brief Löst die Unterbrechung eines Prozesses aus. Wird für den Button verwendet, um das Event zu schedulen.
     */
    void triggerInterruptProcess();

    /**
     * @brief Verarbeitet die in der Warteschlange befindlichen Ereignisse.
     */
    void processEvents();

    /**
     * @brief Plant ein Ereignis zur Ausführung in der Simulation.
     * @param event Das zu planende Ereignis.
     */
    void scheduleEvent(const Event &event);

    /**
     * @brief Aktualisiert die Anzeige der Simulationszeit im UI.
     */
    void updateTimerDisplay();

    /**
     * @brief Startet die ereignisgesteuerte Simulation.
     */
    void startEventSchedulingSimulation();
};

#endif
