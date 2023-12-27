//
// Created by bytedance on 2022/1/2.
//

#include "VoltagePoint.h"

const QList<Line *> &VoltagePoint::getLines() {
    return lines;
}

VoltagePoint::VoltagePoint(const QString& label, bool isZero) : CircuitItem(0, label, "endpoint"), isZero(isZero) {

}

bool VoltagePoint::getIsZero() const {
    return isZero;
}

void VoltagePoint::addLine(Line *line) {
    lines.append(line);
}
