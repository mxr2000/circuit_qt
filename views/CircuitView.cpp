//
// Created by bytedance on 2022/1/3.
//

#include "CircuitView.h"
#include "../items/Resistance.h"
#include "../items/Inductor.h"
#include "../items/Capacitor.h"
#include "../items/Source.h"
#include "../utils/PositionUtil.h"

LineView *CircuitView::findLineView(QPoint p) {
    for( auto lineView : lineViews) {
        QPoint start = lineView->getPoint();
        for (auto linePart : lineView->getLineParts()) {
            if (PositionUtil::isPointOnLine(p, start, linePart)) {
                return lineView;
            }
            start = PositionUtil::getNextPoint(start, linePart->getDirection(), linePart->getLength());
        }
    }
    return nullptr;
}



bool CircuitView::newEndPoint(QPoint p, bool isZero) {
    if (findLineView(p) != nullptr) {
        return false;
    }
    for (auto point : endPointViews) {
        if (point->getPoint().x() == p.x() && point->getPoint().y() == p.y()) {
            return false;
        }
    }
    auto *endPoint = new VoltagePoint(Circuit::getNextLabel(), isZero);
    circuit->getEndPoints().push_back(endPoint);
    endPointViews.push_back(new VoltagePointView(endPoint, p));
    return true;
}


bool CircuitView::newLine(QList<QPoint> path) {
    auto *lineView = new LineView(path[0]);
    VoltagePointView *from = nullptr;
    VoltagePointView *to = nullptr;
    for (auto p : endPointViews) {
        if (p->getPoint().x() == path[0].x() && p->getPoint().y() == path[0].y()) {
            from = p;
        } else if (p->getPoint().x() == path[path.length() - 1].x() && p->getPoint().y() == path[path.length() - 1].y()) {
            to = p;
        }
    }
    if (from == nullptr || to == nullptr) {
        return false;
    }
    lineView->getLine()->setFrom(from->getEndPoint());
    lineView->getLine()->setTo(to->getEndPoint());
    for (int i = 0; i < path.length() - 1; i++) {
        auto *linePart = new LinePart(
                PositionUtil::getLineDirection(path[i], path[i + 1]),
                PositionUtil::getLineLength(path[i], path[i + 1])
                );
        lineView->getLineParts().push_back(linePart);
    }
    circuit->addLine(from->getEndPoint(), to->getEndPoint(), lineView->getLine());
    lineViews.push_back(lineView);

    return true;
}



bool CircuitView::newResistance(QPoint p) {
    return newItem(new Resistance(0, Circuit::getNextLabel()), p);
}

bool CircuitView::newCapacitor(QPoint p) {
    return newItem(new Capacitor(0, Circuit::getNextLabel()), p);
}

bool CircuitView::newSource(QPoint p) {
    return newItem(new Source(0, Circuit::getNextLabel()), p);
}

bool CircuitView::newInductor(QPoint p) {
    return newItem(new Inductor(0, Circuit::getNextLabel()), p);
}

bool CircuitView::removeLineItem(LineItem *item) {
    return false;
}

bool CircuitView::removeLine(LineView *lineView) {
    return false;
}

bool CircuitView::removeEndPoint(VoltagePointView *endPointView) {
    return false;
}

bool CircuitView::moveLineItem(LineItem *item, int newOffset) {
    return false;
}

const QList<VoltagePointView *> &CircuitView::getEndPointViews() const {
    return endPointViews;
}

const QList<LineView *> &CircuitView::getLineViews() const {
    return lineViews;
}

void CircuitView::setCircuit(Circuit *circuit) {
    CircuitView::circuit = circuit;
}

bool CircuitView::newItem(CircuitItem *item, QPoint p) {
    LineView *view = findLineView(p);
    if (view == nullptr) {
        return false;
    }
    view->addItem(item, p);
    return true;
}

LineView *CircuitView::getSelectedLineView(QPoint p) {
    for (auto lineView : lineViews) {
        auto start = lineView->getPoint();
        for (auto linePart : lineView->getLineParts()) {
            if (PositionUtil::isPointOnLine(p, start, linePart)) {
                return lineView;
            }
            start = PositionUtil::getNextPoint(start, linePart->getDirection(), linePart->getLength());
        }
    }
    return nullptr;
}

VoltagePointView *CircuitView::getSelectedEndPointView(QPoint p) {
    for (auto endPointView : endPointViews) {
        if (endPointView->getPoint() == p) {
            return endPointView;
        }
    }
    return nullptr;
}

LineItem *CircuitView::getSelectedLineItem(QPoint p) {
    for (auto lineView : lineViews) {
        auto start = lineView->getPoint();
        for (auto linePart : lineView->getLineParts()) {
            for (auto lineItem : linePart->getLineItems()) {
                auto itemPoint = PositionUtil::getNextPoint(start, linePart->getDirection(), lineItem->getOffset());
                if (p.x() > itemPoint.x() - 2 && p.x() < itemPoint.x() + 2 && p.y() > itemPoint.y() - 2 && p.y() < itemPoint.y() + 2) {
                    return lineItem;
                }
            }
            start = PositionUtil::getNextPoint(start, linePart->getDirection(), linePart->getLength());
        }
    }
    return nullptr;
}

void CircuitView::addEndPointView(VoltagePointView *endPointView) {
    endPointViews.append(endPointView);
}

void CircuitView::addLineView(LineView *lineView) {
    lineViews.append(lineView);

}

Circuit *CircuitView::getCircuit() {
    return circuit;
}



