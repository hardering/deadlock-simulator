#pragma once

#import <QString>
#include <QTableWidget>

#include "Process.h"
#include "Resource.h"
#include "DeadlockRecovery.h"
#include "../qt/Window.h"

class Deadlock : public QObject {
Q_OBJECT

public:

    Deadlock();

public slots:

    void createDeadlock(Window *window);

    QString vectorToQString(const std::vector<int> &vector);


signals:
    
    void setTableData(QTableWidget *table, const QList<QString> &data);
};