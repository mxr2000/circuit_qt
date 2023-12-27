//
// Created by bytedance on 2022/1/6.
//

#ifndef CIRCUIT_SAVECIRCUITDIALOG_H
#define CIRCUIT_SAVECIRCUITDIALOG_H


#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "../views/CircuitView.h"

class SaveDialog : public QDialog {
    Q_OBJECT
private:
    CircuitView *circuitView;
    QLineEdit *nameLineEdit;
    QPushButton *btnSave;
public:
    explicit SaveDialog(CircuitView *circuitView);
};


#endif //CIRCUIT_SAVECIRCUITDIALOG_H
