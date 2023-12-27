//
// Created by bytedance on 2022/1/3.
//

#include "PositionUtil.h"


LineDirection PositionUtil::getLineDirection(QPoint from, QPoint to) {
    if (from.x() == to.x()) {
        return from.y() < to.y() ? LineDirection::Right : LineDirection::Left;
    } else {
        return from.x() < to.x() ? LineDirection::Down : LineDirection::Up;
    }
}

int PositionUtil::getLineLength(QPoint from, QPoint to) {
    if (from.x() == to.x()) {
        return from.y() < to.y() ? to.y() - from.y() : from.y() - to.y();
    } else {
        return from.x() < to.x() ? to.x() - from.x() : from.x()  - to.x();
    }
}

QPoint PositionUtil::getNextPoint(QPoint p, LineDirection direction, int length) {
    switch (direction) {
        case LineDirection::Right:
            return {p.x(), p.y() + length};
        case LineDirection::Left:
            return {p.x(), p.y() - length};
        case LineDirection::Up:
            return {p.x() - length, p.y()};
        case LineDirection::Down:
            return {p.x() + length, p.y()};
    }
}


bool PositionUtil::isPointOnLine(QPoint p, QPoint start, LinePart *linePart) {
    switch (linePart->getDirection()) {
        case LineDirection::Right:
            return p.x() == start.x() && p.y() > start.y() && p.y() < start.y() + linePart->getLength();
        case LineDirection::Left:
            return p.x() == start.x() && p.y() < start.y() && p.y() > start.y() - linePart->getLength();
        case LineDirection::Down:
            return p.y() == start.y() && p.x() > start.x() && p.x() < start.x() + linePart->getLength();
        case LineDirection::Up:
            return p.y() == start.y() && p.x() < start.x() && p.x() > start.x() - linePart->getLength();
    }
    return false;
}