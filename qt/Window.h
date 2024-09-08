#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QRectF>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QPen>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>
#include <QGraphicsProxyWidget>
#include <QGroupBox>
#include "Process.h"
#include "Resource.h"

/**
 * @class Window
 * @brief Diese Klasse erstellt die grafische Benutzeroberfläche (GUI) zur Anzeige und Interaktion mit der Deadlock-Simulation.
 */
class Window : public QWidget {
Q_OBJECT

private:
    QHBoxLayout *layout; /**< Layout der Interaktionselemente. */
    QPushButton *generateDeadlockSituationButton; /**< Button zur Erstellung einer Deadlock-Situation. */
    QPushButton *resetButton; /**< Button zum Zurücksetzen der Tabelle. */
    QPushButton *bankersAlgorithmButton; /**< Button zum Starten des Banker's Algorithmus. */
    QPushButton *interruptProcessButton; /**< Button zum Unterbrechen eines Prozesses. */
    QPushButton *abortProcessButton; /**< Button zum Abbrechen eines Prozesses. */
    QPushButton *processEventsButton; /**< Button zur Bearbeitung von Ereignissen. */
    QPushButton *avoidanceStrategyButton; /**< Button zur Ausführung einer Vermeidungsstrategie. */

    QPushButton *scheduleBankersAlgorithmButton; /**< Button zum Planen des Banker's Algorithmus. */
    QPushButton *scheduleInterruptProcessButton; /**< Button zum Planen der Unterbrechung eines Prozesses. */
    QPushButton *scheduleAbortProcessButton; /**< Button zum Planen des Abbruchs eines Prozesses. */

public:
    QTableWidget *defaultTable; /**< Standardtabelle zur Anzeige der Prozess- und Ressourcenzustände. */

    /**
     * @brief Konstruktor, der das Fenster initialisiert und alle GUI-Elemente erstellt.
     * @param parent Das übergeordnete QWidget-Objekt, standardmäßig nullptr.
     */
    explicit Window(QWidget *parent = nullptr);

    /**
     * @brief Erstellt und fügt die Interaktionselemente wie Buttons dem Fenster hinzu.
     * @return Ein Zeiger auf das erstellte QWidget mit den Interaktionselementen.
     */
    QWidget *setInteractionElements();

    /**
     * @brief Gibt den Stil der Buttons als QString zurück.
     * @return Ein QString, der den Buttonstil definiert.
     */
    QString buttonStyle() const;

    /**
     * @brief Erstellt eine neue Tabelle mit dem gegebenen Titel und den Headern.
     * @param title Der Titel der Tabelle.
     * @param headers Eine Liste der Spaltenüberschriften.
     * @return Ein Zeiger auf die erstellte QTableWidget.
     */
    QTableWidget *createTable(const QString &title, const QStringList &headers);

    /**
     * @brief Erstellt eine leere Tabelle im Fenster.
     */
    void createEmptyTable();

    /**
     * @brief Überprüft, ob die gegebene Tabelle mit Daten gefüllt ist.
     * @param table Zeiger auf die Tabelle, die überprüft werden soll.
     * @return true, wenn die Tabelle gefüllt ist, false andernfalls.
     */
    bool isTableFilled(QTableWidget *table);

public slots:

    /**
     * @brief Setzt Daten in die angegebene Tabelle.
     * @param table Zeiger auf die QTableWidget, in die die Daten eingetragen werden sollen.
     * @param data Liste der Daten, die in die Tabelle eingefügt werden.
     */
    void setTableData(QTableWidget *table, const QList<QString> &data);

    /**
     * @brief Slot, der ausgeführt wird, wenn der Reset-Button gedrückt wird.
     */
    void clickOnResetButton();

    /**
     * @brief Slot, der ausgeführt wird, wenn der Banker's Algorithmus-Button gedrückt wird.
     */
    void clickOnBankersAlgorithmButton();

    /**
     * @brief Slot, der ausgeführt wird, wenn der Button zur Prozessunterbrechung gedrückt wird.
     */
    void clickOnInterruptProcessButton();

    /**
     * @brief Slot, der ausgeführt wird, wenn der Abbruch-Button gedrückt wird.
     */
    void clickOnAbortProcessButton();

    /**
     * @brief Slot, der ausgeführt wird, wenn der Ereignisverarbeitungs-Button gedrückt wird.
     */
    void clickOnProcessEventsButton();

    /**
     * @brief Slot, der ausgeführt wird, wenn der Button zum Planen des Banker's Algorithmus gedrückt wird.
     */
    void clickOnScheduleBankersAlgorithmButton();

    /**
     * @brief Slot, der ausgeführt wird, wenn der Button zum Planen der Prozessunterbrechung gedrückt wird.
     */
    void clickOnScheduleInterruptProcessButton();

    /**
     * @brief Slot, der ausgeführt wird, wenn der Button zum Planen des Prozessabbruchs gedrückt wird.
     */
    void clickOnScheduleAbortProcessButton();

    /**
     * @brief Slot, der ausgeführt wird, wenn der Button zur Vermeidungsstrategie gedrückt wird.
     */
    void clickOnAvoidanceStrategyButton();

    /**
     * @brief Aktualisiert den Status eines Prozesses in der Tabelle, nachdem eine Ressourcenanforderung verarbeitet wurde.
     * @param processId Die ID des Prozesses.
     * @param requestStatus Der Status der Anforderung (true = erfolgreich, false = fehlgeschlagen).
     */
    void updateTableStatus(int processId, bool requestStatus);

signals:

    /**
     * @brief Signal, um eine Anfrage zur Deadlockerzeugung zu senden.
     * @param processes Referenz auf die Liste der Prozesse.
     * @param resources Referenz auf die Liste der Ressourcen.
     * @param table Zeiger auf die Tabelle, in die die Deadlock-Daten eingetragen werden sollen.
     */
    void
    generateDeadlockRequest(std::vector<Process> &processes, std::vector<Resource> &resources, QTableWidget *table);

    /**
     * @brief Signal, um eine Anfrage zum Zurücksetzen der Tabelle zu senden.
     */
    void resetTableRequest();

    /**
     * @brief Signal, um eine Anfrage zum Ausführen des Banker's Algorithmus zu senden.
     */
    void runBankersAlgorithmRequest();

    /**
     * @brief Signal, um eine Anfrage zur Unterbrechung eines Prozesses zu senden.
     */
    void runInterruptProcessRequest();

    /**
     * @brief Signal, um eine Anfrage zum Abbruch eines Prozesses zu senden.
     */
    void runAbortProcessRequest();

    /**
     * @brief Signal, um eine Anfrage zur Verarbeitung von Ereignissen zu senden.
     */
    void runProcessEventsRequest();

    /**
     * @brief Signal, um eine Anfrage zur Planung des Banker's Algorithmus zu senden.
     */
    void runScheduleBankersAlgorithmRequest();

    /**
     * @brief Signal, um eine Anfrage zur Planung der Prozessunterbrechung zu senden.
     */
    void runScheduleInterruptProcessRequest();

    /**
     * @brief Signal, um eine Anfrage zur Planung des Prozessabbruchs zu senden.
     */
    void runScheduleAbortProcessRequest();

    /**
     * @brief Signal, um eine Anfrage zur Ausführung der Vermeidungsstrategie zu senden.
     */
    void runAvoidanceStrategyRequest();
};

#endif
