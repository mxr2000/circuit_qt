//
// Created by bytedance on 2022/1/2.
//

#ifndef CIRCUIT_ITEM_H
#define CIRCUIT_ITEM_H


#include <QString>

class CircuitItem {

protected:
    int value;
    QString label;
    QString name;

public:
    CircuitItem(int value, const QString &label, const QString &name);
    int getValue() const;
    void setValue(int value);
    const QString &getLabel() const;
    void setLabel(const QString &label);
    const QString &getName();
    virtual QString getActualResistance(int frequency) { return ""; }
    virtual bool isResistancePositive() { return true; }
    virtual QString getMeasure() { return ""; }
};


#endif //CIRCUIT_ITEM_H
