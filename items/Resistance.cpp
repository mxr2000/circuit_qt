//
// Created by bytedance on 2022/1/3.
//

#include "Resistance.h"

QString Resistance::getActualResistance(int frequency) {
    float num = 1.0 * value / 1000;
    return "(" + QString::number(num, 'f', 2) + ")";
}
