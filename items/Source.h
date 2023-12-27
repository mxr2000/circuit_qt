//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_SOURCE_H
#define CIRCUIT_SOURCE_H


#include "CircuitItem.h"

class Source : public CircuitItem {
public:
    Source(int value, const QString& label) : CircuitItem(value, label, "source") {}
};


#endif //CIRCUIT_SOURCE_H
