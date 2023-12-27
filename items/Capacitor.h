//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_CAPACITOR_H
#define CIRCUIT_CAPACITOR_H


#include "CircuitItem.h"

class Capacitor : public CircuitItem{
public:
    Capacitor(int value, const QString& label) : CircuitItem(value, label, "capacitor") {}
    QString getActualResistance(int frequency) override;
};


#endif //CIRCUIT_CAPACITOR_H
