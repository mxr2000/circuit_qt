//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_LINEVIEW_H
#define CIRCUIT_LINEVIEW_H

#include <QList>
#include "../items/CircuitItem.h"
#include "../items/Line.h"
#include "../items/Circuit.h"
#include "ItemView.h"
#include "LineItem.h"
#include "VoltagePointView.h"

enum LineDirection {
    Right, Left, Up, Down
};

class LinePart {
private:
    QList<LineItem*> lineItems;
    LineDirection direction;
    int length;
public:
    explicit LinePart(LineDirection d, int length) : direction(d), length(length) {}
    LineDirection getDirection() { return direction; }
    QList<LineItem*>& getLineItems() { return lineItems; }
    void addLineItem(CircuitItem *item, QPoint start, QPoint p);
    void addLineItem(LineItem *lineItem);
    int getLength() const;
    void setLength(int length);
    QPoint getPointByOffset(QPoint start, int offset);
};

class LineView : public ItemView {
private:
    QList<LinePart*> lineParts;
public:
    LineView(QPoint p);
    LineView(VoltagePointView *from, VoltagePointView *to, const QString& label);
    QList<LinePart *> &getLineParts();
    void setLineParts(const QList<LinePart *> &lineParts);
    Line *getLine() const;
    void setLine(Line *line);
    void addItem(CircuitItem *item, QPoint p);
    QList<QPoint> getPoints();

private:
    Line *line;
};


#endif //CIRCUIT_LINEVIEW_H
