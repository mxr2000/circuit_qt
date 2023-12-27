//
// Created by bytedance on 2022/1/3.
//

#include "LineView.h"
#include "../utils/PositionUtil.h"


QList<LinePart *> &LineView::getLineParts() {
    return lineParts;
}

void LineView::setLineParts(const QList<LinePart *> &lineParts) {
    LineView::lineParts = lineParts;
    for (auto linePart : lineParts) {
        for (auto lineItem : linePart->getLineItems()) {
            line->addItem(lineItem->getItem());
        }
    }
}

Line *LineView::getLine() const {
    return line;
}

void LineView::setLine(Line *line) {
    LineView::line = line;
}

void LineView::addItem(CircuitItem *item, QPoint p) {
    auto start = getPoint();
    for (auto linePart : getLineParts()) {
        if (PositionUtil::isPointOnLine(p, start, linePart)) {
            linePart->addLineItem(item, start, p);
            line->addItem(item);
            return;
        }
        start = PositionUtil::getNextPoint(start, linePart->getDirection(), linePart->getLength());
    }
}

QList<QPoint> LineView::getPoints() {
    QList<QPoint> points;
    points.append(getPoint());
    QPoint current = getPoint();
    for (auto linePart : getLineParts()) {
        switch (linePart->getDirection()) {
            case LineDirection::Right:
                current = QPoint(current.x(), current.y() + linePart->getLength());
                break;
            case LineDirection::Left:
                current = QPoint(current.x(), current.y() - linePart->getLength());
                break;
            case LineDirection::Down:
                current = QPoint(current.x() + linePart->getLength(), current.y());
                break;
            case LineDirection::Up:
                current = QPoint(current.x() - linePart->getLength(), current.y());
                break;
        }
        points.append(current);
    }
    return points;
}

LineView::LineView(QPoint p) : ItemView(p) {
    line = new Line(Circuit::getNextLabel());
}

LineView::LineView(VoltagePointView *from, VoltagePointView *to, const QString& label) : ItemView(from->getPoint()) {
    line = new Line(label);
    line->setFrom(from->getEndPoint());
    line->setTo(to->getEndPoint());
    from->getEndPoint()->addLine(line);
    to->getEndPoint()->addLine(line);
}

void LinePart::addLineItem(CircuitItem *item, QPoint start, QPoint p) {
    auto lineItem = new LineItem(item, PositionUtil::getLineLength(start, p));
    lineItems.append(lineItem);
}

int LinePart::getLength() const {
    return length;
}

void LinePart::setLength(int length) {
    LinePart::length = length;
}

QPoint LinePart::getPointByOffset(QPoint start, int offset) {
    switch (direction) {
        case LineDirection::Right:
            return QPoint(start.x(), start.y() + offset);
        case LineDirection::Left:
            return QPoint(start.x(), start.y() - offset);
        case LineDirection::Down:
            return QPoint(start.x() + offset, start.y());
        case LineDirection::Up:
            return QPoint(start.x() - offset, start.y());
    }
}

void LinePart::addLineItem(LineItem *lineItem) {
    lineItems.append(lineItem);
}
