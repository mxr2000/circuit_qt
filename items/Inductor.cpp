//
// Created by bytedance on 2022/1/3.
//

#include "Inductor.h"

QString Inductor::getActualResistance(int frequency) {
    float num = 3.14 * 2 * frequency * value / 1000;
    return "(j" + QString::number(num, 'f', 2) + ")";
}
