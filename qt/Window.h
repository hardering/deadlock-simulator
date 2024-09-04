#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QRectF>

class Window : public QWidget {
Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

    void addResourceGraphics(int id);

    void addProcessGraphics(int id);

public slots:

    void handleResourceAdded(int id);

    void handleProcessAdded(int id);

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    int resourceCount = 0;
    int processCount = 0;

    void centerAndPlaceText(QGraphicsItem *item, const QString &text, int xPosition);
};

#endif
