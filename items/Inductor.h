//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_INDUCTOR_H
#define CIRCUIT_INDUCTOR_H


#include "CircuitItem.h"

class Inductor : public CircuitItem {
public:
    Inductor(int value, const QString& label) : CircuitItem(value, label, "inductor") {}
    QString getActualResistance(int frequency) override;
    QString getMeasure() override { return "mH"; }
};


#endif //CIRCUIT_INDUCTOR_H
