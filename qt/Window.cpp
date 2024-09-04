#include "Window.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QPen>

static const QPen outlinePen(Qt::black, 2);
static const QBrush noBrush(Qt::transparent);

Window::Window(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Deadlock Simulator");
    resize(800, 600);
    setStyleSheet("background-color: white");

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setGeometry(0, 0, 800, 600);
}

void Window::centerAndPlaceText(QGraphicsItem *item, const QString &text, int xOffset) {
    QGraphicsTextItem *label = scene->addText(text, QFont("Arial", 16));
    label->setDefaultTextColor(Qt::black);

    QRectF itemBounds = item->boundingRect();
    QRectF labelBounds = label->boundingRect();

    QPointF labelPosition(
            xOffset + (itemBounds.width() - labelBounds.width()) / 2,
            (itemBounds.height() - labelBounds.height()) / 2
    );
    label->setPos(item->pos() + labelPosition);
}

void Window::addResourceGraphics(int id) {
    int rectWidth = 100;
    int gap = 100;
    int xPosition = resourceCount * (rectWidth + gap);

    QGraphicsRectItem *rectangle = scene->addRect(xPosition, 0, rectWidth, 50, outlinePen, noBrush);
    centerAndPlaceText(rectangle, "R" + QString::number(id), xPosition);

    resourceCount++;
}

void Window::addProcessGraphics(int id) {
    int circleWidth = 50;
    int gap = 100;
    int xPosition = processCount * (circleWidth + gap);

    QGraphicsEllipseItem *circle = scene->addEllipse(xPosition, 100, circleWidth, circleWidth, outlinePen, noBrush);
    centerAndPlaceText(circle, "P" + QString::number(id), xPosition);

    processCount++;
}

void Window::handleResourceAdded(int id) {
    addResourceGraphics(id);
}

void Window::handleProcessAdded(int id) {
    addProcessGraphics(id);
}
