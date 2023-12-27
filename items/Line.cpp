//
// Created by bytedance on 2022/1/2.
//

#include "Line.h"

Line::Line(const QString &label) : CircuitItem(0, label, "line") {

}

VoltagePoint *Line::getFrom() const {
    return from;
}

void Line::setFrom(VoltagePoint *from) {
    Line::from = from;
}

VoltagePoint *Line::getTo() const {
    return to;
}

void Line::setTo(VoltagePoint *to) {
    Line::to = to;
}

void Line::addItem(CircuitItem *item) {
    items.append(item);
}

const QList<CircuitItem *>& Line::getItems() {
    return items;
}

VoltagePoint *Line::getAnother(VoltagePoint *p) {
    if (from == p) {
        return to;
    } else if (to == p) {
        return from;
    }
    return nullptr;
}
