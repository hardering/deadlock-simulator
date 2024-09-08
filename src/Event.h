#pragma once

#include <iostream>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

/**
 * @class Event
 * @brief Die Klasse Event repräsentiert ein Ereignis, das zu einem bestimmten Zeitpunkt ausgeführt wird.
 */
class Event {

public:
    int executeTime;          /**< Die Ausführungszeit des Ereignisses. */
    function<void()> action;  /**< Die Funktion, die ausgeführt wird, wenn das Ereignis eintritt. */
    std::string description;  /**< Eine Beschreibung des Ereignisses. */

    /**
     * @brief Konstruktor, der ein Ereignis erstellt.
     * @param action Die Aktion, die beim Auftreten des Ereignisses ausgeführt wird.
     * @param executeTime Die Zeit, zu der das Ereignis ausgeführt werden soll.
     * @param desc Eine kurze Beschreibung des Ereignisses.
     */
    Event(std::function<void()> action, int executeTime, std::string desc);

    /**
     * @brief Vergleichsoperator zum Sortieren von Ereignissen nach Ausführungszeit.
     * @param other Ein anderes Event-Objekt zum Vergleich.
     * @return true, wenn das aktuelle Ereignis nach dem anderen ausgeführt wird, false sonst.
     */
    bool operator<(const Event &other) const;
};
