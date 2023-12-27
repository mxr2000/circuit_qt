//
// Created by bytedance on 2022/1/5.
//

#ifndef CIRCUIT_CIRCUITVIEWDAO_H
#define CIRCUIT_CIRCUITVIEWDAO_H

#include <QJsonObject>
#include <QJsonArray>
#include "../views/CircuitView.h"
#include "../items/CircuitItem.h"

class DocumentIO {
public:
    static QString saveCircuitView(CircuitView *circuitView, const QString &name);
    static CircuitView *loadCircuitView(const QJsonObject &root);

    static CircuitItem *generateItem(const QString &name, const QString &label, int value);

private:
    static QJsonObject getJsonObjectByPoint(QPoint p);

    static bool checkCircuitView(CircuitView *circuitView);
};


#endif //CIRCUIT_CIRCUITVIEWDAO_H
