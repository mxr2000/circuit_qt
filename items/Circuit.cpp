//
// Created by bytedance on 2022/1/3.
//

#include "Circuit.h"

bool Circuit::isValid() {
    for (auto p : endPoints) {
        QSet<VoltagePoint*> set;
        if (!canPointCirculate(p, set, p)) {
            return false;
        }
    }
    return true;
}

bool Circuit::canPointCirculate(VoltagePoint *p, QSet<VoltagePoint*>& visited, VoltagePoint *target) {
    for (auto line : p->getLines()) {
        auto another = line->getAnother(p);
        if (another == target) {
            return true;
        }
        if (!visited.contains(another)) {
            visited.insert(another);
            if (canPointCirculate(another, visited, target)) {
                return true;
            }
            visited.remove(another);
        }
    }
    return false;
}

QList<VoltagePoint *> &Circuit::getEndPoints() {
    return endPoints;
}

QString Circuit::getNextLabel() {
    return "label";
}

void Circuit::addLine(VoltagePoint *from, VoltagePoint *to, Line *line) {

}


