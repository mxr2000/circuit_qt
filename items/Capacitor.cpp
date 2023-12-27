//
// Created by bytedance on 2022/1/3.
//

#include "Capacitor.h"

QString Capacitor::getActualResistance(int frequency) {
    float num = 1000000.0f / (2 * 3.14f * frequency * value);
    return "(-j" + QString::number(num, 'f', 2) + ")";
}
