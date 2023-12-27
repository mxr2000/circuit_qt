//
// Created by bytedance on 2022/1/6.
//

#ifndef CIRCUIT_EQUATIONGENERATOR_H
#define CIRCUIT_EQUATIONGENERATOR_H


#include <QString>
#include "../items/Circuit.h"

class ResultCalculator {
public:
    static QString generateEquation(Circuit *circuit, int frequency);
    static Line *getSourceLine(const QList<Line*> &lines);
    static QString generateSeries(const QList<Line*>& lines, Line *sourceLine, int frequency);
    static QString generateParallel(const QList<Line*> lines, Line *sourceLine, int frequency);
};


#endif //CIRCUIT_EQUATIONGENERATOR_H
