//
// Created by bytedance on 2022/1/2.
//

#include "CircuitItem.h"

int CircuitItem::getValue() const {
    return value;
}

void CircuitItem::setValue(int value) {
    CircuitItem::value = value;
}

const QString &CircuitItem::getLabel() const {
    return label;
}

void CircuitItem::setLabel(const QString &label) {
    CircuitItem::label = label;
}

CircuitItem::CircuitItem(int value, const QString &label, const QString &name) : value(value), label(label), name(name) {}

const QString &CircuitItem::getName() {
    return name;
}
