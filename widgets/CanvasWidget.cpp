//
// Created by bytedance on 2022/1/2.
//

#include "CanvasWidget.h"
#include "../dao/DocumentIO.h"

CanvasWidget::CanvasWidget(PropertiesHolder *propertiesHolder) : propertiesHolder(propertiesHolder) {
    initPens();
    initCircuit();
    initStates();
    initContextMenu();
    repaint();
}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(palette().dark().color());

    int offsetX = (width() - cellSize * horizontalSize) / 2;
    int offsetY = (height() - cellSize * verticalSize) / 2;
    painter.translate(offsetX, offsetY);

    drawMesh(painter);
    drawEndPoints(painter);
    drawLines(painter);
    drawItems(painter);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    auto pos = event->pos();
    int horizontalOffset = (width() - cellSize * horizontalSize) / 2;
    int verticalOffset = (height() - cellSize * verticalSize) / 2;
    int x = (pos.y() - verticalOffset) / cellSize;
    int y = (pos.x() - horizontalOffset) / cellSize;
    if (x < 0 || x >= verticalSize || y < 0 || y >= horizontalSize) {
        return;
    }
    if (event->button() == Qt::RightButton) {
        auto globalPosition = event->globalPosition();
        currentState->onCellClickedRightButton(QPoint(x, y), globalPosition.toPoint());
    } else {
        onCellClicked(QPoint(x, y));
    }
}

void CanvasWidget::drawMesh(QPainter& painter) const {
    painter.setPen(meshPen);
    painter.setBrush(backgroundBrush);
    painter.drawRect(QRect(0, 0, cellSize * horizontalSize, cellSize * verticalSize));
    painter.setBrush(meshBrush);
    for (int i = 0; i < verticalSize; i++) {
        for (int j = 0; j < horizontalSize; j++) {
            painter.drawEllipse(QPoint(j * cellSize + cellSize / 2, i * cellSize + cellSize / 2), 2, 2);
        }
    }


}

void CanvasWidget::drawEndPoints(QPainter& painter) {
    if (circuitView == nullptr) {
        return;
    }
    painter.setBrush(endPointBrush);
    painter.setPen(endPointPen);
    for (auto pointView : circuitView->getEndPointViews()) {
        painter.save();
        if (pointView == selectedEndPointView) {
            painter.setPen(selectedPen);
            painter.setBrush(selectedBrush);
        }
        auto point = pointView->getPoint();
        painter.drawEllipse(QRect(
                point.y() * cellSize + cellSize / 2 - 2,
                point.x() * cellSize + cellSize / 2 - 2,
                4,
                4)
        );
        if (pointView->getEndPoint()->getIsZero()) {
            painter.drawLine(
                    QPoint(point.y() * cellSize + cellSize / 2, point.x() * cellSize + cellSize / 2),
                    QPoint(point.y() * cellSize + cellSize / 2, point.x() * cellSize + cellSize / 2 + cellSize)
                    );
            painter.drawEllipse(QPoint(point.y() * cellSize + cellSize / 2, point.x() * cellSize + cellSize / 2 + cellSize), 2, 2);
        }
        painter.restore();
    }
    painter.setPen(Qt::NoBrush);
}

void CanvasWidget::drawLines(QPainter &painter) {
    if (circuitView == nullptr) {
        return;
    }
    painter.setPen(linePen);
    for (auto lineView : circuitView->getLineViews()) {
        painter.save();
        if (lineView == selectedLineView) {
            painter.setPen(selectedPen);
        }
        auto points = lineView->getPoints();
        for (int i = 0; i < points.length() - 1; i++) {
            auto from = points[i];
            auto to = points[i + 1];
            painter.drawLine(
                    from.y() * cellSize + cellSize / 2,
                    from.x() * cellSize + cellSize / 2,
                    to.y() * cellSize + cellSize / 2,
                    to.x() * cellSize + cellSize / 2
                    );
        }
        painter.restore();
    }
}

void CanvasWidget::drawItems(QPainter &painter) {
    if (circuitView == nullptr) {
        return;
    }
    for (auto lineView : circuitView->getLineViews()) {
        auto points = lineView->getPoints();
        auto lineParts = lineView->getLineParts();
        for (int i = 0; i < lineParts.length(); i++) {
            auto linePart = lineParts[i];
            auto start = points[i];
            for (auto lineItem : linePart->getLineItems()) {
                auto name = lineItem->getItem()->getName();
                auto position = linePart->getPointByOffset(start, lineItem->getOffset());
                if (name == "source") {
                    drawSource(painter, position, linePart->getDirection(), lineItem);
                } else if (name == "capacitor") {
                    drawCapacitor(painter, position, linePart->getDirection(), lineItem);
                } else if (name == "inductor") {
                    drawInductor(painter, position, linePart->getDirection(), lineItem);
                } else if (name == "resistance") {
                    drawResistance(painter, position, linePart->getDirection(), lineItem);
                }
            }
        }
    }
}

void CanvasWidget::initPens() {
    meshPen = QPen(Qt::lightGray, 1);
    linePen = QPen(Qt::black, 2);
    itemPen = QPen(Qt::black, 2);
    endPointPen = QPen(Qt::black, 2);
    selectedPen = QPen(Qt::red, 2);

    meshBrush = QBrush(Qt::lightGray);
    resistanceBrush = QBrush(Qt::white);
    sourceBrush = QBrush(Qt::white);
    inductorBrush = QBrush(Qt::white);
    capacitorBrush = QBrush(Qt::white);
    endPointBrush = QBrush(Qt::black);
    backgroundBrush = QBrush(Qt::white);
    selectedBrush = QBrush(Qt::red);
}

void CanvasWidget::drawResistance(QPainter &painter, QPoint p, LineDirection direction, LineItem *lineItem) {
    painter.save();
    if (lineItem == selectedLineItem) {
        painter.setPen(selectedPen);
        painter.setBrush(selectedBrush);
    } else {
        painter.setPen(itemPen);
        painter.setBrush(resistanceBrush);
    }

    QRect rect(
            p.y() * cellSize + cellSize / 2 - 10,
            p.x() * cellSize + cellSize / 2 - 5,
            20,
            10
            );
    if (direction == LineDirection::Up || direction == LineDirection:: Down) {
        rect = QRect(
                p.y() * cellSize + cellSize / 2 - 5,
                p.x() * cellSize + cellSize / 2 - 10,
                10,
                20
                );
    }
    painter.drawRect(rect);
    painter.restore();
}

void CanvasWidget::drawCapacitor(QPainter &painter, QPoint p, LineDirection direction, LineItem *lineItem) {
    painter.save();
    if (lineItem == selectedLineItem) {
        painter.setPen(selectedPen);
        painter.setBrush(selectedBrush);
    } else {
        painter.setBrush(capacitorBrush);
        painter.setPen(Qt::NoPen);
    }
    QPoint from1(p.y() * cellSize + cellSize / 2 - 5, p.x() * cellSize + cellSize / 2 - 10);
    QPoint to1(p.y() * cellSize + cellSize / 2 - 5, p.x() * cellSize + cellSize / 2 + 10);
    QPoint from2(p.y() * cellSize + cellSize / 2 + 5, p.x() * cellSize + cellSize / 2 - 10);
    QPoint to2(p.y() * cellSize + cellSize / 2 + 5, p.x() * cellSize + cellSize / 2 + 10);
    QRect rect(from1, to2);
    if (direction == LineDirection::Up || direction == LineDirection:: Down) {
        from1 = QPoint(p.y() * cellSize + cellSize / 2 - 10, p.x() * cellSize + cellSize / 2 - 5);
        to1 = QPoint(p.y() * cellSize + cellSize / 2 + 10, p.x() * cellSize + cellSize / 2 - 5);
        from2 = QPoint(p.y() * cellSize + cellSize / 2 - 10, p.x() * cellSize + cellSize / 2 + 5);
        to2 = QPoint(p.y() * cellSize + cellSize / 2 + 10, p.x() * cellSize + cellSize / 2 + 5);
        rect = QRect(from1, to2);
    }
    painter.drawRect(rect);
    painter.setPen(itemPen);
    painter.drawLine(from1, to1);
    painter.drawLine(from2, to2);

    painter.restore();
}

void CanvasWidget::drawInductor(QPainter &painter, QPoint p, LineDirection direction, LineItem *lineItem) {
    painter.save();
    if (lineItem == selectedLineItem) {
        painter.setPen(selectedPen);
        painter.setBrush(selectedBrush);
    } else {
        painter.setPen(itemPen);
        painter.setBrush(inductorBrush);
    }

    QRect rect(
            p.y() * cellSize + cellSize / 2 - 10,
            p.x() * cellSize + cellSize / 2 - 5,
            20,
            10
    );
    if (direction == LineDirection::Up || direction == LineDirection:: Down) {
        rect = QRect(
                p.y() * cellSize + cellSize / 2 - 5,
                p.x() * cellSize + cellSize / 2 - 10,
                10,
                20
        );

    }
    painter.drawRect(rect);
    painter.drawLine(rect.topLeft(), rect.bottomRight());
    painter.drawLine(rect.topRight(), rect.bottomLeft());

    painter.restore();
}

void CanvasWidget::drawSource(QPainter &painter, QPoint p, LineDirection direction, LineItem *lineItem) {
    painter.save();
    if (lineItem == selectedLineItem) {
        painter.setPen(selectedPen);
        painter.setBrush(selectedBrush);
    } else {
        painter.setPen(itemPen);
        painter.setBrush(sourceBrush);
    }

    QRect rect(
            p.y() * cellSize + cellSize / 2 - 10,
            p.x() * cellSize + cellSize / 2 - 10,
            20,
            20
            );
    painter.drawEllipse(rect);

    painter.restore();
}

void CanvasWidget::onCellClicked(QPoint p) {
    currentState->onCellClicked(p);
;}

void CanvasWidget::changeState(StateType stateType) {
    currentState = states[stateType];
    propertiesHolder->setStateLabel(currentState->getName());
    repaint();
}

void CanvasWidget::initStates() {
    states.clear();
    states.insert(StateType::DrawingLine, new DrawingLineState(this, circuitView));
    states.insert(StateType::None, new NoneState(this, circuitView));
    states.insert(StateType::Selected, new SelectedState(this, circuitView));
    states.insert(StateType::SetSource, new SetSourceState(this, circuitView));
    states.insert(StateType::SetCapacitor, new SetCapacitorState(this, circuitView));
    states.insert(StateType::SetEndPoint, new SetEndPointState(this, circuitView));
    states.insert(StateType::SetInductor, new SetInductorState(this, circuitView));
    states.insert(StateType::SetResistance, new SetResistanceState(this, circuitView));
    states.insert(StateType::SetZeroEndPoint, new SetZeroEndPointState(this, circuitView));

    changeState(StateType::None);
}

void CanvasWidget::initCircuit() {
    auto *circuit = new Circuit;
    circuitView = new CircuitView;
    circuitView->setCircuit(circuit);
    circuitView->newEndPoint(QPoint(20, 20));
    circuitView->newEndPoint(QPoint(30, 20), true);
    circuitView->newLine({QPoint(20, 20), QPoint(20, 10), QPoint(30, 10), QPoint(30, 20)});
    circuitView->newLine({QPoint(20, 20), QPoint(30, 20)});
    circuitView->newSource(QPoint(25, 10));
    circuitView->newResistance(QPoint(20, 15));
    circuitView->newCapacitor(QPoint(30, 15));
}

bool CanvasWidget::setSelectedItems(QPoint p) {
    selectedEndPointView = nullptr;
    selectedLineItem = nullptr;
    selectedLineView = nullptr;
    bool changed = false;
    if ((selectedLineItem = circuitView->getSelectedLineItem(p)) != nullptr) {
        changed = true;
        propertiesHolder->setPropertyLineEdits(selectedLineItem->getItem());
    } else if ((selectedEndPointView = circuitView->getSelectedEndPointView(p)) != nullptr) {
        changed = true;
        propertiesHolder->setPropertyLineEdits(selectedEndPointView->getEndPoint());
    } else if ((selectedLineView = circuitView->getSelectedLineView(p)) != nullptr) {
        changed = true;
        propertiesHolder->setPropertyLineEdits(selectedLineView->getLine());
    } else {
        propertiesHolder->clearPropertyLineEdits();
    }
    repaint();
    return changed;
}

CircuitView *CanvasWidget::getCircuitView() {
    return circuitView;
}

void CanvasWidget::newCircuitView() {
    circuitView = new CircuitView;
    auto circuit = new Circuit;
    circuitView->setCircuit(circuit);
    repaint();
    initStates();
    initContextMenu();
}

void CanvasWidget::showLineContextMenu(QPoint point, QPoint globalPosition) {
    if (selectedLineView != nullptr) {
        rightClickedPoint = point;
        lineMenu->exec(globalPosition);
    }
}

void CanvasWidget::initContextMenu() {
    lineMenu = new QMenu;
    auto newResistanceAction = new QAction(tr("new resistance"));
    auto newSourceAction = new QAction(tr("new source"));
    auto newInductorAction = new QAction(tr("new inductor"));
    auto newCapacitor = new QAction(tr("new capacitor"));
    auto pasteAction = new QAction(tr("paste"));
    lineMenu->addAction(newResistanceAction);
    lineMenu->addAction(newSourceAction);
    lineMenu->addAction(newInductorAction);
    lineMenu->addAction(newCapacitor);
    lineMenu->addAction(pasteAction);
    connect(newResistanceAction, &QAction::triggered, [=]{ circuitView->newResistance(rightClickedPoint); repaint(); });
    connect(newSourceAction, &QAction::triggered, [=]{ circuitView->newSource(rightClickedPoint); repaint(); });
    connect(newInductorAction, &QAction::triggered, [=]{ circuitView->newInductor(rightClickedPoint); repaint(); });
    connect(newCapacitor, &QAction::triggered, [=]{ circuitView->newCapacitor(rightClickedPoint); repaint(); });
    connect(pasteAction, &QAction::triggered, [=]{
        if (copiedItem != nullptr) {
            circuitView->newItem(DocumentIO::generateItem(copiedItem->getName(), copiedItem->getLabel(), copiedItem->getValue()), rightClickedPoint);
            repaint();
        } else {
            propertiesHolder->setWarningMessageLabel("No selected item to copy!");
        }
    });

    itemMenu = new QMenu;
    auto copyAction = new QAction(tr("copy"));
    itemMenu->addAction(copyAction);
    connect(copyAction, &QAction::triggered, [=]{
        auto item = circuitView->getSelectedLineItem(rightClickedPoint);
        if (item != nullptr) {
            copiedItem = item->getItem();
        } else {
            propertiesHolder->setWarningMessageLabel("No copied item to paste!");
        }
    });
}

void CanvasWidget::updateSelectedItemProperties(const QString& label, int value) {
    if (selectedLineItem != nullptr) {
        CircuitItem *item = selectedLineItem->getItem();
        item->setLabel(label);
        item->setValue(value);
    } else if (selectedLineView != nullptr) {
        Line *line = selectedLineView->getLine();
        line->setLabel(label);
    } else if (selectedEndPointView != nullptr) {
        VoltagePoint *endPoint = selectedEndPointView->getEndPoint();
        endPoint->setLabel(label);
    } else {
        propertiesHolder->setErrorMessageLabel("No items selected!");
    }
}

void CanvasWidget::setCircuitView(CircuitView *circuitView) {
    this->circuitView = circuitView;
    initStates();
    initContextMenu();
    repaint();
}

void CanvasWidget::showItemContextMenu(QPoint point, QPoint globalPosition) {
    if (selectedLineItem != nullptr) {
        rightClickedPoint = point;
        itemMenu->exec(globalPosition);
    }
}




