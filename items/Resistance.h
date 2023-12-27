//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_RESISTANCE_H
#define CIRCUIT_RESISTANCE_H


#include "CircuitItem.h"

class Resistance : public CircuitItem {
public:
    Resistance(int value, const QString& label) : CircuitItem(value, label, "resistance") {}
    QString getActualResistance(int frequency) override;
    QString getMeasure() override { return "om"; }
};


#endif //CIRCUIT_RESISTANCE_H
