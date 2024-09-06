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

private:
    QHBoxLayout *layout;
    QPushButton *generateDeadlockSituationButton;
    QPushButton *resetButton;
    
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

    void onResetClicked();

signals:

    void generateDeadlockSituationRequest();

    void resetTableRequest();

};


#endif
