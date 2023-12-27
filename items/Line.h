//
// Created by bytedance on 2022/1/2.
//

#ifndef CIRCUIT_LINE_H
#define CIRCUIT_LINE_H


#include <QList>
#include "CircuitItem.h"
#include "VoltagePoint.h"

class VoltagePoint;

class Line : public CircuitItem {
private:
    VoltagePoint *from;
    VoltagePoint *to;
    QList<CircuitItem*> items;

public:
    Line(const QString& label);
    VoltagePoint *getFrom() const;
    void setFrom(VoltagePoint *from);
    VoltagePoint *getTo() const;
    void setTo(VoltagePoint *to);
    void addItem(CircuitItem *item);
    const QList<CircuitItem*>& getItems();
    VoltagePoint *getAnother(VoltagePoint *p);
};


#endif //CIRCUIT_LINE_H
