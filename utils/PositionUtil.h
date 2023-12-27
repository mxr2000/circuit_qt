//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_POINTUTIL_H
#define CIRCUIT_POINTUTIL_H


#include <QtCore/qpoint.h>
#include "../views//LineView.h"

class PositionUtil {
public:
    static bool isPointOnLine(QPoint p, QPoint start, LinePart *linePart);
    static QPoint getNextPoint(QPoint p, LineDirection direction, int length);
    static LineDirection getLineDirection(QPoint from, QPoint to);
    static int getLineLength(QPoint from, QPoint to);
};


#endif //CIRCUIT_POINTUTIL_H
