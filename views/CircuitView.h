//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_CIRCUITVIEW_H
#define CIRCUIT_CIRCUITVIEW_H


#include <QList>
#include <QtCore/qpoint.h>
#include "VoltagePointView.h"
#include "LineView.h"

class CircuitView {
private:
    QList<VoltagePointView*> endPointViews;
    QList<LineView*> lineViews;
    Circuit *circuit;

    LineView *findLineView(QPoint p);


public:
    void addEndPointView(VoltagePointView *endPointView);
    void addLineView(LineView *lineView);

    bool newItem(CircuitItem *item, QPoint p);
    bool newEndPoint(QPoint p, bool isZero = false);
    bool newLine(QList<QPoint> path);
    bool newResistance(QPoint p);
    bool newCapacitor(QPoint p);
    bool newSource(QPoint p);
    bool newInductor(QPoint p);
    const QList<VoltagePointView *> &getEndPointViews() const;
    const QList<LineView *> &getLineViews() const;
    bool removeLineItem(LineItem *item);

    void setCircuit(Circuit *circuit);

    bool removeLine(LineView *lineView);
    bool removeEndPoint(VoltagePointView * endPointView);

    bool moveLineItem(LineItem *item, int newOffset);
    Circuit *getCircuit();
public:

    LineView* getSelectedLineView(QPoint p);
    VoltagePointView* getSelectedEndPointView(QPoint p);
    LineItem* getSelectedLineItem(QPoint p);

};


#endif //CIRCUIT_CIRCUITVIEW_H
