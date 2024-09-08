#pragma once

#include <iostream>
#include <vector>
#include <QString>
#include "Resource.h"
#include "DeadlockDetector.h"
#include "DeadlockRecovery.h"

/**
 * @class Process
 * @brief Repräsentiert einen Prozess, der Ressourcen anfordern und freigeben kann.
 */
class Process {
private:
    int pid;  ///< Prozess-ID
    int priority;  ///< Priorität des Prozesses
    std::vector<int> maxResources;  ///< Maximale Ressourcenanforderungen des Prozesses
    std::vector<int> allocatedResources;  ///< Aktuell zugewiesene Ressourcen
    std::vector<int> neededResources;  ///< Noch benötigte Ressourcen
    std::vector<int> currentRequest;  ///< Aktuelle Ressourcenanforderung
    std::vector<int> initialNeededResources;  ///< Ursprünglich benötigte Ressourcen
    std::vector<int> initialAllocatedResources;  ///< Ursprünglich zugewiesene Ressourcen
    std::string status;  ///< Status des Prozesses
    DeadlockDetector* deadlockDetector;  ///< Zeiger auf den Deadlock-Detektor
    bool isInterrupted = false;  ///< Zeigt an, ob der Prozess unterbrochen wurde

public:
    /**
     * @brief Konstruktor, um einen neuen Prozess zu erstellen.
     * @param id Prozess-ID
     * @param maxResources Maximale Ressourcenanforderungen des Prozesses
     * @param priority Priorität des Prozesses
     */
    Process(int id, const std::vector<int>& maxResources, int priority);

    /**
     * @brief Fordert Ressourcen für den Prozess an.
     * @param request Die Anzahl der angeforderten Ressourcen
     * @param resources Die verfügbaren Ressourcen
     * @return true, wenn die Ressourcen erfolgreich zugewiesen wurden; false, wenn die Anforderung abgelehnt wurde
     */
    bool requestResources(const std::vector<int>& request, std::vector<Resource>& resources);

    /**
     * @brief Gibt die aktuell zugewiesenen Ressourcen frei.
     * @param resources Die verfügbaren Ressourcen, zu denen die freigegebenen Ressourcen zurückgeführt werden
     */
    void releaseResources(std::vector<Resource>& resources);

    /**
     * @brief Überprüft, ob der Prozess abgeschlossen ist.
     * @return true, wenn der Prozess alle benötigten Ressourcen erhalten hat; false andernfalls
     */
    bool isFinished() const;

    /**
     * @brief Gibt die Prozess-ID zurück.
     * @return Die Prozess-ID
     */
    int getPID() const;

    /**
     * @brief Gibt die Priorität des Prozesses zurück.
     * @return Die Priorität des Prozesses
     */
    int getPriority() const;

    /**
     * @brief Gibt die aktuell zugewiesenen Ressourcen zurück.
     * @return Ein Vektor mit den zugewiesenen Ressourcen
     */
    const std::vector<int>& getAllocatedResources() const;

    /**
     * @brief Gibt die noch benötigten Ressourcen zurück.
     * @return Ein Vektor mit den noch benötigten Ressourcen
     */
    std::vector<int>& getNeededResources();

    /**
     * @brief Gibt die noch benötigten Ressourcen (als Konstante) zurück.
     * @return Ein Vektor mit den noch benötigten Ressourcen
     */
    const std::vector<int>& getNeededResources() const;

    /**
     * @brief Gibt den aktuellen Zustand des Prozesses zurück.
     * @param processes Die Liste aller Prozesse
     * @param resources Die Liste aller Ressourcen
     * @return Der Zustand des Prozesses als QString
     */
    QString getState(const std::vector<Process>& processes, const std::vector<Resource>& resources);

    /**
     * @brief Weist dem Prozess die angeforderten Ressourcen zu.
     * @param request Die angeforderten Ressourcen
     */
    void allocateResources(const std::vector<int>& request);

    /**
     * @brief Gibt die angegebenen Ressourcen frei.
     * @param request Die Anzahl der freizugebenden Ressourcen
     */
    void releaseResources(const std::vector<int>& request);

    /**
     * @brief Unterbricht den Prozess.
     */
    void interrupt();

    /**
     * @brief Setzt den Prozess auf seinen Ursprungszustand zurück.
     */
    void reset();

    /**
     * @brief Hebt die Unterbrechung des Prozesses auf.
     */
    void clearInterruption();

    /**
     * @brief Gibt die maximalen Ressourcenanforderungen des Prozesses zurück.
     * @return Ein Vektor mit den maximalen Ressourcenanforderungen
     */
    const std::vector<int>& getMaxResources() const;

    /**
     * @brief Gibt die aktuelle Ressourcenanforderung des Prozesses zurück.
     * @return Ein Vektor mit den aktuellen Ressourcenanforderungen
     */
    const std::vector<int>& getCurrentRequest() const;
};
