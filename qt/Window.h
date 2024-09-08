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

class Window : public QWidget {
Q_OBJECT

private:
    QHBoxLayout *layout;
    QPushButton *generateDeadlockSituationButton;
    QPushButton *resetButton;
    QPushButton *bankersAlgorithmButton;
    QPushButton *interruptProcessButton;
    QPushButton *abortProcessButton;
    QPushButton *processEventsButton;

    QPushButton *scheduleBankersAlgorithmButton;
    QPushButton *scheduleInterruptProcessButton;
    QPushButton *scheduleAbortProcessButton;

public:
    QTableWidget *defaultTable;

    explicit Window(QWidget *parent = nullptr);

    QWidget *setInteractionElements();

    QString buttonStyle() const;

    QTableWidget *createTable(const QString &title, const QStringList &headers);

    void createEmptyTable();

    bool isTableFilled(QTableWidget *table);

public slots:

    void setTableData(QTableWidget *table, const QList<QString> &data);

    void clickOnResetButton();

    void clickOnBankersAlgorithmButton();

    void clickOnInterruptProcessButton();

    void clickOnAbortProcessButton();

    void clickOnProcessEventsButton();

    void clickOnScheduleBankersAlgorithmButton();

    void clickOnScheduleInterruptProcessButton();

    void clickOnScheduleAbortProcessButton();

    void updateTableStatus(int processId, bool requestStatus);


signals:

    void
    generateDeadlockRequest(std::vector<Process> &processes, std::vector<Resource> &resources, QTableWidget *table);

    void resetTableRequest();

    void runBankersAlgorithmRequest();

    void runInterruptProcessRequest();

    void runAbortProcessRequest();

    void runProcessEventsRequest();

    void runScheduleBankersAlgorithmRequest();

    void runScheduleInterruptProcessRequest();

    void runScheduleAbortProcessRequest();
};


#endif
