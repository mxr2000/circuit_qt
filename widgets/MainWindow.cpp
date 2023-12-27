//
// Created by bytedance on 2022/1/2.
//

#include <QPushButton>
#include "MainWindow.h"
#include "CanvasWidget.h"
#include "../dialogs/SaveDialog.h"
#include "../dialogs/OpenDialog.h"
#include "../utils/ResultCalculator.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QStatusBar>
#include <QSizePolicy>

MainWindow::MainWindow() {
    initResultPanel();
    initControlPanel();
    initPropertiesPanel();
    //createMenu();
    initStatusBar();

    auto centerWidget = new QWidget;
    auto layout = new QGridLayout;
    centerWidget->setLayout(layout);

    painterWidget = new CanvasWidget(this);

    layout->addWidget(actionsPanel, 0, 0, 1, 2);
    layout->addWidget(painterWidget, 1, 0, 1, 2);
    layout->addWidget(propertiesPanel, 2, 0);
    layout->addWidget(resultPanel, 2, 1);
    layout->addWidget(statusLabel, 3, 0);
    layout->addWidget(messageLabel, 3, 1);
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 0);

    setCentralWidget(centerWidget);
}

void MainWindow::initControlPanel() {
    actionsPanel = new QWidget;
    auto layout = new QHBoxLayout;

    btnCapacitor = new QPushButton(tr("capacitor"));
    btnEndPoint = new QPushButton(tr("point"));
    btnInductor = new QPushButton(tr("inductor"));
    btnLine = new QPushButton(tr("line"));
    btnResistance = new QPushButton(tr("resistance"));
    btnSource = new QPushButton(tr("source"));
    btnZeroEndPoint = new QPushButton(tr("zero"));
    auto strategyStyle = "background-color: rgb(153, 204, 102);";
    btnCapacitor->setStyleSheet(strategyStyle);
    btnEndPoint->setStyleSheet(strategyStyle);
    btnInductor->setStyleSheet(strategyStyle);
    btnLine->setStyleSheet(strategyStyle);
    btnResistance->setStyleSheet(strategyStyle);
    btnSource->setStyleSheet(strategyStyle);
    btnZeroEndPoint->setStyleSheet(strategyStyle);


    btnNewCircuit = new QPushButton(tr("new"));
    btnOpenCircuit = new QPushButton(tr("open"));
    btnSaveCircuit = new QPushButton(tr("save"));
    auto actionStyle = "background-color: rgb(255, 204, 255);";
    btnNewCircuit->setStyleSheet(actionStyle);
    btnOpenCircuit->setStyleSheet(actionStyle);
    btnSaveCircuit->setStyleSheet(actionStyle);

    layout->addWidget(btnNewCircuit);
    layout->addWidget(btnOpenCircuit);
    layout->addWidget(btnSaveCircuit);

    layout->addStretch();

    layout->addWidget(btnEndPoint);
    layout->addWidget(btnLine);
    layout->addWidget(btnResistance);
    layout->addWidget(btnSource);
    layout->addWidget(btnCapacitor);
    layout->addWidget(btnInductor);
    layout->addWidget(btnZeroEndPoint);

    connect(btnNewCircuit, &QPushButton::clicked, [=]{ painterWidget->newCircuitView(); });
    connect(btnSaveCircuit, &QPushButton::clicked, [=]{ (new SaveDialog(painterWidget->getCircuitView()))->show(); });
    connect(btnOpenCircuit, &QPushButton::clicked, [=]{ (new OpenDialog(painterWidget))->show(); });

    connect(btnLine, &QPushButton::clicked, [=]{ painterWidget->changeState(StateType::DrawingLine); });
    connect(btnEndPoint, &QPushButton::clicked, [=]{ painterWidget->changeState(StateType::SetEndPoint); });
    connect(btnInductor, &QPushButton::clicked, [=]{ painterWidget->changeState(StateType::SetInductor); });
    connect(btnResistance, &QPushButton::clicked, [=]{ painterWidget->changeState(StateType::SetResistance); });
    connect(btnSource, &QPushButton::clicked, [=]{ painterWidget->changeState(StateType::SetSource); });
    connect(btnCapacitor, &QPushButton::clicked, [=]{ painterWidget->changeState(StateType::SetCapacitor); });
    connect(btnZeroEndPoint, &QPushButton::clicked, [=]{ painterWidget->changeState(StateType::SetZeroEndPoint); });

    actionsPanel->setLayout(layout);
}

void MainWindow::setItemLineEdits(CircuitItem *item) {
    typeLabel->setText(item->getName());
    labelLineEdit->setText(item->getLabel());
    valueLineEdit->setText(tr("%1").arg(item->getValue()));
}

void MainWindow::setPropertyLineEdits(CircuitItem *item) {
    valueLineEdit->setText(tr("%1").arg(item->getValue()));
    typeLabel->setText(item->getName());
    labelLineEdit->setText(item->getLabel());
    measureLabel->setText(item->getMeasure());
}

void MainWindow::clearPropertyLineEdits() {
    valueLineEdit->setText("");
    typeLabel->setText("");
    labelLineEdit->setText("");
}

void MainWindow::setItemProperties() {
    QString label = labelLineEdit->text();
    QString valueStr = valueLineEdit->text();
    bool ok;
    int value = valueStr.toInt(&ok);
    if (ok) {
        painterWidget->updateSelectedItemProperties(label, value);
    } else {
        setErrorMessageLabel("value is not an integer!");
    }
}

void MainWindow::initStatusBar() {
    statusLabel = new QLabel("Strategy: None");
    messageLabel = new QLabel("Message: None");
    //statusBar()->addWidget(statusLabel = new QLabel("Strategy: None"));
    //statusBar()->addWidget(messageLabel = new QLabel("Message: None"));
}

void MainWindow::setStateLabel(const QString &state) {
    statusLabel->setText("Strategy: " + state);
}

void MainWindow::setPlainMessageLabel(const QString &message) {
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::black);
    messageLabel->setPalette(pe);
    messageLabel->setText(message);
}

void MainWindow::setWarningMessageLabel(const QString &message) {
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::yellow);
    messageLabel->setPalette(pe);
    messageLabel->setText(message);
}

void MainWindow::setErrorMessageLabel(const QString &message) {
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    messageLabel->setPalette(pe);
    messageLabel->setText(message);
}

void MainWindow::initResultPanel() {
    resultPanel = new QGroupBox(tr("result"));
    auto layout = new QVBoxLayout;
    auto topLayout = new QGridLayout;

    frequencyLineEdit = new QLineEdit(tr("50"));
    frequencyLineEdit->setMaximumWidth(50);
    resultLineEdit = new QLineEdit;
    resultLineEdit->setMinimumWidth(200);

    btnShowResult = new QPushButton(tr("calculate"));
    btnShowResult->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    btnShowResult->setStyleSheet("background-color: rgb(0, 253, 255);");

    topLayout->addWidget(new QLabel(tr("frequency")), 0, 0);
    topLayout->addWidget(new QLabel(tr("result")), 0, 1);
    topLayout->addWidget(frequencyLineEdit, 0, 1);
    topLayout->addWidget(resultLineEdit, 1, 1);
    topLayout->addWidget(btnShowResult, 2, 1);

    auto topWidget = new QWidget;
    topWidget->setLayout(topLayout);

    layout->addWidget(topWidget);
    layout->addStretch();

    connect(btnShowResult, &QPushButton::clicked, [=]{

        bool ok;
        auto frequencyStr = frequencyLineEdit->text();
        int value = frequencyStr.toInt(&ok);
        if (ok && value > 0) {
            resultLineEdit->setText(ResultCalculator::generateEquation(painterWidget->getCircuitView()->getCircuit(), value));
            //(new ResultDialog(painterWidget->getCircuitView()->getCircuit(), value))->show();
        } else {
            //resultLineEdit->setText("frequency is not a valid positive integer!");
            setErrorMessageLabel("frequency is not a valid positive integer!");
        }
    });

    resultPanel->setLayout(layout);
}

void MainWindow::initPropertiesPanel() {
    propertiesPanel = new QGroupBox(tr("properties"));
    auto layout = new QFormLayout;

    typeLabel = new QLabel;
    labelLineEdit = new QLineEdit;
    valueLineEdit = new QLineEdit;
    measureLabel = new QLabel;

    btnSetProperties = new QPushButton(tr("reset"));
    btnSetProperties->setStyleSheet("background-color: rgb(255, 255, 0);");

    layout->addRow(new QLabel(tr("type")), typeLabel);
    layout->addRow(new QLabel(tr("label")), labelLineEdit);
    layout->addRow(new QLabel(tr("value")), valueLineEdit);
    layout->addRow(new QLabel(tr("measure")), measureLabel);
    layout->addRow(new QLabel, btnSetProperties);

    connect(btnSetProperties, &QPushButton::clicked, [=]{ setItemProperties(); });

    propertiesPanel->setLayout(layout);
}
