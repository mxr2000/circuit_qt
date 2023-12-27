//
// Created by bytedance on 2022/1/2.
//

#ifndef CIRCUIT_MAINWINDOW_H
#define CIRCUIT_MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QCheckBox>
#include "CanvasWidget.h"

class MainWindow : public QMainWindow, public PropertiesHolder {
    Q_OBJECT

private:
    QPushButton *btnLine;
    QPushButton *btnEndPoint;
    QPushButton *btnSource;
    QPushButton *btnResistance;
    QPushButton *btnInductor;
    QPushButton *btnCapacitor;
    QPushButton *btnZeroEndPoint;

    QPushButton *btnOpenCircuit;
    QPushButton *btnSaveCircuit;
    QPushButton *btnNewCircuit;

    QWidget *actionsPanel;
    QGroupBox *propertiesPanel;
    QGroupBox *resultPanel;
    CanvasWidget *painterWidget;

    QLabel *typeLabel;
    QLineEdit *labelLineEdit;
    QLineEdit *valueLineEdit;
    QLabel *measureLabel;

    QLineEdit *frequencyLineEdit;
    QLineEdit *resultLineEdit;

    QPushButton *btnSetProperties;
    QPushButton *btnShowResult;

    QLabel *statusLabel;
    QLabel *messageLabel;

private:
    void initControlPanel();
    void initPropertiesPanel();
    void initResultPanel();
    void initStatusBar();

private:
    void setItemProperties();

private:
    void setItemLineEdits(CircuitItem *item);

public:
    MainWindow();

public:
    void setPropertyLineEdits(CircuitItem *item) override;
    void clearPropertyLineEdits() override;
    void setStateLabel(const QString &state) override;
    void setPlainMessageLabel(const QString &message) override;
    void setWarningMessageLabel(const QString &message) override;
    void setErrorMessageLabel(const QString &message) override;

};


#endif //CIRCUIT_MAINWINDOW_H
