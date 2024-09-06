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

class Window : public QWidget {
Q_OBJECT

public:
    QTableWidget *resourceTable;
    QTableWidget *processTable;
    QTableWidget *waitingListTable;

    explicit Window(QWidget *parent = nullptr);

    QWidget *setInteractionElements();

    QString buttonStyle() const;

    QTableWidget *createTable(const QString &title, const QStringList &headers);

    QPushButton *getPresetButton() const;

    void createEmptyTable();

private:
    QHBoxLayout *layout;
    QPushButton *generateDeadlockSituationButton;

public slots:

    void setTableData(QTableWidget *table, const QList<QString> &data);

signals:

    void generateDeadlockSituationRequest();

};


#endif
