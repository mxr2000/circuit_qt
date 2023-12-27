//
// Created by bytedance on 2022/1/2.
//

#ifndef CIRCUIT_ENDPOINT_H
#define CIRCUIT_ENDPOINT_H


#include "CircuitItem.h"
#include "Line.h"

class Line;

class VoltagePoint : public CircuitItem {
private:
    QList<Line*> lines;
    bool isZero;

public:
    VoltagePoint(const QString& label, bool isZero = false);
    const QList<Line*>& getLines();
    void addLine(Line *line);

    bool getIsZero() const;
};


#endif //CIRCUIT_ENDPOINT_H
