#pragma once

#include <iostream>
#include <vector>

/**
 * @class Resource
 * @brief Die Klasse Resource repräsentiert eine Ressource im System, die von Prozessen verwendet werden kann.
 */
class Resource {
private:
    int totalInstances;       /**< Die Gesamtzahl der Instanzen dieser Ressource */
    int availableInstances;   /**< Die Anzahl der verfügbaren Instanzen dieser Ressource */

public:
    /**
     * @brief Konstruktor, der die Gesamtzahl der Instanzen einer Ressource initialisiert.
     * @param total Die Gesamtzahl der Instanzen der Ressource.
     */
    explicit Resource(int total);

    /**
     * @brief Versucht, eine bestimmte Anzahl von Instanzen dieser Ressource zuzuweisen.
     * @param instances Die Anzahl der zuzuweisenden Instanzen.
     * @return true, wenn die Zuweisung erfolgreich war, false, wenn nicht genügend Instanzen verfügbar sind.
     */
    bool allocate(int instances);

    /**
     * @brief Gibt eine bestimmte Anzahl von Instanzen dieser Ressource frei.
     * @param instances Die Anzahl der freizugebenden Instanzen.
     */
    void release(int instances);

    /**
     * @brief Gibt die Anzahl der aktuell verfügbaren Instanzen zurück.
     * @return Die Anzahl der verfügbaren Instanzen.
     */
    int getAvailableInstances() const;

    /**
     * @brief Gibt die Gesamtzahl der Instanzen dieser Ressource zurück.
     * @return Die Gesamtzahl der Instanzen.
     */
    int getTotalInstances() const;

    /**
     * @brief Gibt die Details einer Liste von Ressourcen auf der Konsole aus.
     * @param resources Eine Referenz auf einen Vektor von Resource-Objekten.
     */
    void printResources(const std::vector<Resource> &resources);
};
