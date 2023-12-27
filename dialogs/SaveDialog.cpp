//
// Created by bytedance on 2022/1/6.
//

#include <QHBoxLayout>
#include <QLabel>
#include "SaveDialog.h"
#include "../dao/DocumentIO.h"

SaveDialog::SaveDialog(CircuitView *circuitView) : circuitView(circuitView) {
    auto layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignCenter);
    auto label = new QLabel;
    nameLineEdit = new QLineEdit;
    btnSave = new QPushButton(tr("save"));
    layout->addWidget(new QLabel(tr("file name:")));
    layout->addWidget(nameLineEdit);
    layout->addWidget(btnSave);
    layout->addWidget(label);
    auto hWidget = new QWidget;
    hWidget->setLayout(layout);
    setLayout(layout);
    connect(btnSave, &QPushButton::clicked, [=]{
        QString suggestion = DocumentIO::saveCircuitView(circuitView, nameLineEdit->text() + ".json");
        label->setText(suggestion);
    });
}
