//
// Created by bytedance on 2022/1/5.
//


#include <QFile>
#include <QJsonDocument>
#include "DocumentIO.h"
#include "../items//Inductor.h"
#include "../items/Capacitor.h"
#include "../items/Source.h"
#include "../items/Line.h"
#include "../items/Resistance.h"
#include "../views/CircuitView.h"
#include "../views/VoltagePointView.h"

QString DocumentIO::saveCircuitView(CircuitView *circuitView, const QString &name) {
    if (!checkCircuitView(circuitView)) {
        return "duplicated end point's names";
    }
    QJsonObject root;
    QJsonArray endPoints;
    QJsonArray lineViews;
    for (auto endPointView : circuitView->getEndPointViews()) {
        QJsonObject endPointViewObj;
        endPointViewObj["point"] = getJsonObjectByPoint(endPointView->getPoint());
        endPointViewObj["label"] = endPointView->getEndPoint()->getLabel();
        endPointViewObj["is_zero"] = endPointView->getEndPoint()->getIsZero();
        endPoints.append(endPointViewObj);
    }
    for (auto lineView : circuitView->getLineViews()) {
        QJsonObject lineViewObj;
        Line *line = lineView->getLine();
        lineViewObj["from"] = line->getFrom()->getLabel();
        lineViewObj["to"] = line->getTo()->getLabel();
        lineViewObj["label"] = line->getLabel();
        QJsonArray lineParts;
        for (auto linePart : lineView->getLineParts()) {
            QJsonObject linePartObj;
            linePartObj["direction"] = linePart->getDirection();
            linePartObj["length"] = linePart->getLength();
            QJsonArray lineItems;
            for (auto lineItem : linePart->getLineItems()) {
                QJsonObject lineItemObj;
                CircuitItem *item = lineItem->getItem();
                lineItemObj["type"] = item->getName();
                lineItemObj["label"] = item->getLabel();
                lineItemObj["value"] = item->getValue();
                lineItemObj["offset"] = lineItem->getOffset();
                lineItems.append(lineItemObj);
            }
            linePartObj["items"] = lineItems;
            lineParts.append(linePartObj);
        }
        lineViewObj["parts"] = lineParts;
        lineViews.append(lineViewObj);
    }
    root["end_points"] = endPoints;
    root["lines"] = lineViews;

    QFile file("circuits/" + name);
    if (file.exists()) {
        return "file already exists!";
    }
    if (!file.open(QIODevice::WriteOnly)) {
        return "could not open file!";
    } else {
        file.write(QJsonDocument(root).toJson());
        return "successfully saved the circuit";
    }
}

QJsonObject DocumentIO::getJsonObjectByPoint(QPoint p) {
    QJsonObject obj;
    obj["x"] = p.x();
    obj["y"] = p.y();
    return obj;
}

CircuitView *DocumentIO::loadCircuitView(const QJsonObject &root) {
    auto circuitView = new CircuitView;
    auto circuit = new Circuit;
    circuitView->setCircuit(circuit);
    auto endPointViewsRaw = root["end_points"];
    auto lineViewsRaw = root["lines"];
    QMap<QString, VoltagePointView*> endPointViewMap;
    if (endPointViewsRaw.isArray()) {
        auto endPointViewsArray = endPointViewsRaw.toArray();
        for (auto endPointViewRaw : endPointViewsArray) {
            if (!endPointViewRaw.isObject()) {
                continue;
            }
            auto endPointViewObj = endPointViewRaw.toObject();
            auto pointObj = endPointViewObj["point"].toObject();
            int x = pointObj["x"].toInt();
            int y = pointObj["y"].toInt();
            QPoint p(x, y);
            QString label = endPointViewObj["label"].toString();
            bool isZero = endPointViewObj["is_zero"].toBool();
            auto *endPoint = new VoltagePoint(label, isZero);
            auto *endPointView = new VoltagePointView(endPoint, p);
            endPointViewMap.insert(label, endPointView);
            circuitView->addEndPointView(endPointView);
        }
    }
    if (lineViewsRaw.isArray()) {
        auto lineViewsArray = lineViewsRaw.toArray();
        for (auto lineViewRaw : lineViewsArray) {
            auto lineViewObj = lineViewRaw.toObject();
            QString label = lineViewObj["label"].toString();
            auto fromEndPointView = endPointViewMap[lineViewObj["from"].toString()];
            auto toEndPointView = endPointViewMap[lineViewObj["to"].toString()];
            auto lineView = new LineView(fromEndPointView, toEndPointView, label);
            QList<LinePart*> lineParts;
            auto linePartsRaw = lineViewObj["parts"];
            if (!linePartsRaw.isNull()) {
                auto linePartsArray = linePartsRaw.toArray();
                for (auto linePartRaw : linePartsArray) {
                    if (linePartsRaw.isNull()) {
                        continue;
                    }
                    auto linePartObj = linePartRaw.toObject();
                    int direction = linePartObj["direction"].toInt();
                    int length = linePartObj["length"].toInt();
                    auto linePart = new LinePart(static_cast<LineDirection>(direction), length);
                    auto lineItemsRaw = linePartObj["items"];
                    if (!lineItemsRaw.isNull()) {
                        auto lineItemsArray = lineItemsRaw.toArray();
                        for (auto lineItemRaw : lineItemsArray) {
                            auto lineItemObj = lineItemRaw.toObject();
                            CircuitItem *item = generateItem(lineItemObj["type"].toString(), lineItemObj["label"].toString(), lineItemObj["value"].toInt());
                            int offset = lineItemObj["offset"].toInt();
                            auto lineItem = new LineItem(item, offset);
                            linePart->addLineItem(lineItem);
                        }
                    }
                    lineParts.append(linePart);
                }
                lineView->setLineParts(lineParts);
            }
            circuitView->addLineView(lineView);
        }
    }
    for (auto endPointView : endPointViewMap) {
        circuit->getEndPoints().append(endPointView->getEndPoint());
    }
    for (auto endPoint : circuit->getEndPoints()) {
        qDebug() << endPoint->getLabel();
        for (auto line : endPoint->getLines()) {
            qDebug() << "--" << line->getLabel() << " ";
            for (auto item : line->getItems()) {
                qDebug() << "----" << item->getName() << " " <<  item->getLabel() << " " << item->getValue();
            }
        }
    }
    return circuitView;
}

CircuitItem *DocumentIO::generateItem(const QString &name, const QString &label, int value) {
    if (name == "inductor") {
        return new Inductor(value, label);
    } else if (name == "capacitor") {
        return new Capacitor(value, label);
    } else if (name == "source") {
        return new Source(value, label);
    } else if (name == "resistance") {
        return new Resistance(value, label);
    }
    return nullptr;
}

bool DocumentIO::checkCircuitView(CircuitView *circuitView) {
    QSet<QString> endPointLabels;
    for (auto endPointView : circuitView->getEndPointViews()) {
        auto label = endPointView->getEndPoint()->getLabel();
        if (endPointLabels.contains(label)) {
            return false;
        }
        endPointLabels.insert(label);
    }
    return true;
}
