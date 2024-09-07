#include "Window.h"
#include "Process.h"
#include "Resource.h"
#include "Deadlock.h"

Window::Window(QWidget *parent)
        : QWidget(parent),
          defaultTable(nullptr),
          generateDeadlockSituationButton(nullptr),
          resetButton(nullptr) {


    setWindowTitle("Deadlock Simulator");
    resize(800, 300);

    auto *tablesGroup = new QGroupBox(this);
    auto *main = new QHBoxLayout(this);


    layout = new QHBoxLayout(tablesGroup);

    main->addWidget(tablesGroup, 1);

    QWidget *interactionContainer = setInteractionElements();
    interactionContainer->setMinimumSize(200, 200);
    main->addWidget(interactionContainer, 1);

    createEmptyTable();
}

QWidget *Window::setInteractionElements() {
    auto *interactionElementsContainer = new QWidget(this);
    auto *interactionElementsLayout = new QVBoxLayout(interactionElementsContainer);


    generateDeadlockSituationButton = new QPushButton("Generate Deadlock", this);
    generateDeadlockSituationButton->setStyleSheet(buttonStyle());
    interactionElementsLayout->addWidget(generateDeadlockSituationButton);

    resetButton = new QPushButton("Reset", this);
    resetButton->setStyleSheet(buttonStyle());
    interactionElementsLayout->addWidget(resetButton);

    bankersAlgorithmButton = new QPushButton("Run Banker's Algorithm", this);
    bankersAlgorithmButton->setStyleSheet(buttonStyle());
    interactionElementsLayout->addWidget(bankersAlgorithmButton);

    interactionElementsLayout->addStretch();

    connect(generateDeadlockSituationButton, &QPushButton::clicked, this, [this]() {
        std::vector<Process> processes;
        std::vector<Resource> resources;
        emit generateDeadlockRequest(processes, resources, defaultTable);
    });

    connect(resetButton, &QPushButton::clicked, this, &Window::onResetClicked);
    return interactionElementsContainer;
}

void Window::onResetClicked() {
    defaultTable->setRowCount(0);
    emit resetTableRequest();
}


void Window::createEmptyTable() {
    defaultTable = createTable("Process and Resource allocation",
                               {"Process Id", "State", "After Allocation",
                                "Requested Resources"});
}

QTableWidget *Window::createTable(const QString &title, const QStringList &headers) {
    auto *label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);

    auto *table = new QTableWidget(0, headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setMinimumSize(700, 200);

    table->setStyleSheet("gridline-color: darkgrey;");

    auto *tableLayout = new QVBoxLayout();
    tableLayout->addWidget(label);
    tableLayout->addWidget(table);
    tableLayout->addStretch(1);

    layout->addLayout(tableLayout);

    return table;
}

void Window::setTableData(QTableWidget *table, const QList<QString> &data) {
    int row = table->rowCount();
    table->insertRow(row);
    for (int i = 0; i < data.size(); ++i) {
        table->setItem(row, i, new QTableWidgetItem(data[i]));
    }
}

bool Window::isTableFilled(QTableWidget *table) {
    return table->rowCount() > 0;
}

QString Window::buttonStyle() const {
    return "QPushButton {"
           "  font: 14px;"
           "  border: none;"
           "  padding: 6px;"
           "  background-color: black;"
           "  color: white;"
           "  border-radius: 4px;"
           "}"
           "QPushButton:hover {"
           "  background-color: darkgrey;"
           "}";
}

