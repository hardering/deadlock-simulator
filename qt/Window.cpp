#include "Window.h"
#include <QFont>
#include <QPen>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>
#include <QGraphicsProxyWidget>
#include <QGroupBox>

Window::Window(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Deadlock Simulator");
    resize(800, 300);

    auto *tablesGroup = new QGroupBox();
    auto *main = new QHBoxLayout(this);


    layout = new QHBoxLayout(tablesGroup);

    main->addWidget(tablesGroup, 1);

    QWidget * interactionContainer = setInteractionElements();
    interactionContainer->setMinimumSize(100, 200);
    main->addWidget(interactionContainer, 1);

    createEmptyTable();
}

QTableWidget *Window::createTable(const QString &title, const QStringList &headers) {
    auto *label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);

    auto *table = new QTableWidget(0, headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setMinimumSize(500, 200);

    auto *tableLayout = new QVBoxLayout();
    tableLayout->addWidget(label);
    tableLayout->addWidget(table);
    tableLayout->addStretch(1);

    layout->addLayout(tableLayout);

    return table;
}

void Window::createEmptyTable() {
    resourceTable = createTable("Resources", {"Prozess-Id", "Gehaltene Ressourcen", "Angeforderte Ressourcen"});
}

void Window::setTableData(QTableWidget *table, const QList<QString> &data) {
    int row = table->rowCount();
    table->insertRow(row);
    for (int i = 0; i < data.size(); ++i) {
        table->setItem(row, i, new QTableWidgetItem(data[i]));
    }
}

QWidget *Window::setInteractionElements() {
    auto *interactionElementsContainer = new QWidget;
    auto *interactionElementsLayout = new QVBoxLayout(interactionElementsContainer);


    generateDeadlockSituationButton = new QPushButton("Preset", this);
    generateDeadlockSituationButton->setStyleSheet(buttonStyle());
    interactionElementsLayout->addWidget(generateDeadlockSituationButton);
    interactionElementsLayout->addStretch();

    connect(generateDeadlockSituationButton, &QPushButton::clicked, this, &Window::generateDeadlockSituationRequest);
    return interactionElementsContainer;
}

QPushButton *Window::getPresetButton() const {
    return generateDeadlockSituationButton;
}

QString Window::buttonStyle() const {
    return "QPushButton {"
           "  font: 14px;"
           "  border: 1px solid black;"
           "  padding: 6px;"
           "  background-color: white;"
           "  color: black;"
           "}"
           "QPushButton:hover {"
           "  background-color: silver;"
           "}";
}

