//
// Created by bytedance on 2022/1/6.
//

#include <QDir>
#include <QVBoxLayout>
#include <QJsonDocument>
#include "OpenDialog.h"
#include "../dao/DocumentIO.h"

OpenDialog::OpenDialog(CanvasWidget *painterWidget) : painterWidget(painterWidget) {
    QDir dir("circuits");
    fileListWidget = new QListWidget;
    btnLoadFile = new QPushButton(tr("open"));
    btnCancel = new QPushButton(tr("cancel"));
    auto layout = new QVBoxLayout;
    auto list = dir.entryInfoList();
    for (int i = 0 ; i < list.length(); i++) {
        QFileInfo fileInfo = list.at(i);
        fileListWidget->addItem(fileInfo.fileName());
    }
    layout->addWidget(fileListWidget);
    auto bottomWidget = new QWidget;
    auto bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(btnCancel);
    bottomLayout->addWidget(btnLoadFile);
    bottomWidget->setLayout(bottomLayout);
    layout->addWidget(bottomWidget);
    setLayout(layout);
    connect(btnLoadFile, &QPushButton::clicked, [=]{
        auto currentItem = fileListWidget->currentItem() ;
        if (currentItem != nullptr) {
            QFile file("circuits/" + currentItem->text());
            if (!file.open(QIODevice::ReadOnly)) {
                qWarning("Couldn't open save file.");
                return;
            }
            QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));
            auto circuitView = DocumentIO::loadCircuitView(doc.object());
            if (circuitView != nullptr) {
                painterWidget->setCircuitView(circuitView);
            }
        }
    });
}
