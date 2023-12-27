//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_CIRCUIT_H
#define CIRCUIT_CIRCUIT_H


#include <QList>
#include <QSet>
#include "VoltagePoint.h"

class Circuit {
private:
    QList<VoltagePoint*> endPoints;
    QString name;

public:
    bool isValid();
    static bool canPointCirculate(VoltagePoint *p, QSet<VoltagePoint*>& visited, VoltagePoint *target);
    static QString getNextLabel();
    QList<VoltagePoint *> &getEndPoints();
    void addLine(VoltagePoint *from, VoltagePoint *to, Line *line);
};


#endif //CIRCUIT_CIRCUIT_H
