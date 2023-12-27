//
// Created by bytedance on 2022/1/6.
//

#ifndef CIRCUIT_OPENCIRCUITDIALOG_H
#define CIRCUIT_OPENCIRCUITDIALOG_H


#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include "../widgets/CanvasWidget.h"

class OpenDialog : public QDialog {
    Q_OBJECT
private:
    QListWidget *fileListWidget;
    QPushButton *btnLoadFile;
    QPushButton *btnCancel;
    CanvasWidget *painterWidget;
public:
    explicit OpenDialog(CanvasWidget *painterWidget);
};


#endif //CIRCUIT_OPENCIRCUITDIALOG_H
