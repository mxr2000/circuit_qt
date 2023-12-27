//
// Created by bytedance on 2022/1/6.
//

#include "ResultCalculator.h"

QString ResultCalculator::generateEquation(Circuit *circuit, int frequency) {
    auto endpoints = circuit->getEndPoints();
    if (endpoints.length() != 2) {
        return "Invalid number of end points";
    }
    VoltagePoint *zeroEndPoint = endpoints[0]->getIsZero() ? endpoints[0] : endpoints[1];
    auto lines = zeroEndPoint->getLines();
    auto sourceLine = getSourceLine(lines);
    if (lines.length() == 2) {
        return generateSeries(lines, sourceLine, frequency);
    } else {
        return generateParallel(lines, sourceLine, frequency);
    }
    return "The circuit is invalid!";
}

Line *ResultCalculator::getSourceLine(const QList<Line*> &lines) {
    for (auto line : lines) {
        for (auto item : line->getItems()) {
            if (item->getName() == "source") {
                return line;
            }
        }
    }
    return nullptr;
}

QString ResultCalculator::generateSeries(const QList<Line *>& lines, Line *sourceLine, int frequency) {
    QString result = "";
    Line *line1 = lines[0];
    Line *line2 = lines[1];
    for (auto item : line1->getItems()) {
        if (item->getName() == "source") {
            result += "-(" + QString::number(item->getValue()) + ")";
        } else {
            result += "+" + item->getActualResistance(frequency) + "I";
        }
    }
    for (auto item : line2->getItems()) {
        if (item->getName() == "source") {
            result += "-(" + QString::number(item->getValue()) + ")";
        } else {
            result += "+" + item->getActualResistance(frequency) + "I";
        }
    }
    result += " = 0";
    return result;
}

QString ResultCalculator::generateParallel(const QList<Line *> lines, Line *sourceLine, int frequency) {
    if (sourceLine == nullptr) {
        return "No source";
    }
    QString result;
    QList<QString> lineResults;
    for (auto line : lines) {
        if (line == sourceLine) {
            continue;
        }
        QString lineResult;
        for (auto item : line->getItems()) {
            lineResult += " +" + item->getActualResistance(frequency);
        }
        lineResults.append(lineResult);
    }
    for (auto item : sourceLine->getItems()) {
        if (item->getName() == "source") {
            result += "-(" + QString::number(item->getValue()) + ")";
        } else {
            result += "+" + item->getActualResistance(frequency) + "I";
        }
    }
    result += " + I / (";
    for (const auto& lineResult : lineResults) {
        result += "+ 1 / (" + lineResult + ")";
    }
    result += ") = 0";
    return result;
}
