//
// Created by bytedance on 2022/1/3.
//

#include "Strategy.h"
#include "../dao/DocumentIO.h"

void SetItemState::onCellClicked(QPoint point) {
    CircuitItem *newItem = DocumentIO::generateItem(item->getName(), item->getLabel(), item->getValue());
    auto lineView = circuitView->getSelectedLineView(point);
    auto occupiedLineItem = circuitView->getSelectedLineItem(point);
    if (lineView != nullptr && occupiedLineItem == nullptr) {
        lineView->addItem(newItem, point);
    }
    auto circuit = circuitView->getCircuit();
    for (auto endPoint : circuit->getEndPoints()) {
        qDebug() << endPoint->getLabel();
        for (auto line : endPoint->getLines()) {
            qDebug() << "--" << line->getLabel() << " ";
            for (auto item : line->getItems()) {
                qDebug() << "----" << item->getName() << " " <<  item->getLabel() << " " << item->getValue();
            }
        }
    }
    stateHolder->changeState(StateType::Selected);
}

void DrawingLineState::onCellClicked(QPoint point) {
    if (points.empty()) {
        from = circuitView->getSelectedEndPointView(point);
        if (from == nullptr) {
            clearAndGoBack();
        } else {
            points.append(point);
        }
    } else {
        to = circuitView->getSelectedEndPointView(point);
        if (from == to) {
            clearAndGoBack();
        } else if (to == nullptr) {
            auto last = points.last();
            if (point.x() == last.x() || point.y() == last.y()) {
                points.append(point);
            } else {
                clearAndGoBack();
            }
        } else {
            points.append(point);
            circuitView->newLine(points);
            clearAndGoBack();
        }
    }
}

void DrawingLineState::clearAndGoBack() {
    from = to = nullptr;
    points.clear();
    stateHolder->changeState(StateType::None);
}

void NoneState::onCellClicked(QPoint point) {
    if (stateHolder->setSelectedItems(point)) {
        stateHolder->changeState(StateType::Selected);
    }
}


void SelectedState::onCellClicked(QPoint point) {
    if (!stateHolder->setSelectedItems(point)) {
        stateHolder->changeState(StateType::None);
    }
}

void SelectedState::setView(ItemView *view) {
    this->view = view;
}

void SelectedState::onEnteringState(QPoint p) {

}

void SelectedState::onCellClickedRightButton(QPoint p, QPoint globalPosition) {
    if (circuitView->getSelectedLineItem(p) != nullptr) {
        stateHolder->showItemContextMenu(p, globalPosition);
    } else if (circuitView->getSelectedLineView(p) != nullptr) {
        stateHolder->showLineContextMenu(p, globalPosition);
    }
}


void SetEndPointState::onCellClicked(QPoint point) {
    if (circuitView->getSelectedLineView(point) != nullptr ||
    circuitView->getSelectedEndPointView(point) != nullptr ||
    circuitView->getSelectedLineItem(point) != nullptr) {
        stateHolder->changeState(StateType::None);
    }
    circuitView->newEndPoint(point);
    stateHolder->changeState(StateType::None);
}

void SetZeroEndPointState::onCellClicked(QPoint point) {
    if (circuitView->getSelectedLineView(point) != nullptr ||
        circuitView->getSelectedEndPointView(point) != nullptr ||
        circuitView->getSelectedLineItem(point) != nullptr) {
        stateHolder->changeState(StateType::None);
    }
    circuitView->newEndPoint(point, true);
    stateHolder->changeState(StateType::None);
}
