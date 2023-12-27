#include <QApplication>
#include <QPushButton>
#include "widgets/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow win;
    win.resize(600, 800);
    win.show();
    return QApplication::exec();
}
