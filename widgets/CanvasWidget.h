//
// Created by bytedance on 2022/1/2.
//

#ifndef CIRCUIT_PAINTERWIDGET_H
#define CIRCUIT_PAINTERWIDGET_H


#include <QtWidgets/qwidget.h>
#include <QPaintEvent>
#include <QPainter>
#include <QMenu>
#include "../views/CircuitView.h"
#include "../strategies/Strategy.h"

class PropertiesHolder {
public:
    virtual void setPropertyLineEdits(CircuitItem *item) = 0;
    virtual void clearPropertyLineEdits() = 0;
    virtual void setStateLabel(const QString &state) = 0;
    virtual void setPlainMessageLabel(const QString &message) = 0;
    virtual void setWarningMessageLabel(const QString &message) = 0;
    virtual void setErrorMessageLabel(const QString &message) = 0;
};

class CanvasWidget : public QWidget, StateHolder {
    Q_OBJECT
private:
    CircuitView *circuitView;
public:
    void setCircuitView(CircuitView *circuitView);
    CircuitView *getCircuitView();
private:
    int cellSize = 10;
    int horizontalSize = 50;
    int verticalSize = 35;

private:
    void drawMesh(QPainter& painter) const;
    void drawEndPoints(QPainter& painter);
    void drawLines(QPainter& painter);
    void drawItems(QPainter& painter);

    void drawResistance(QPainter& painter, QPoint p, LineDirection direction, LineItem *lineItem);
    void drawCapacitor(QPainter& painter, QPoint p, LineDirection direction, LineItem *lineItem);
    void drawInductor(QPainter& painter, QPoint p, LineDirection direction, LineItem *lineItem);
    void drawSource(QPainter& painter, QPoint p, LineDirection direction, LineItem *lineItem);


private:
    CircuitItem *copiedItem = nullptr;
    QPoint rightClickedPoint;
    QMenu *lineMenu;
    QMenu *itemMenu;

private:
    void initPens();
    void initStates();
    void initCircuit();
    void initContextMenu();

private:
    LineItem *selectedLineItem = nullptr;
    LineView *selectedLineView = nullptr;
    VoltagePointView *selectedEndPointView = nullptr;

public:
    bool setSelectedItems(QPoint p) override;

public:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void onCellClicked(QPoint p);

public:
    void updateSelectedItemProperties(const QString& label, int value);

private:
    PropertiesHolder *propertiesHolder;
    QMap<StateType, Strategy*> states;
    Strategy* currentState;

public:
    void changeState(StateType stateType) override;
    void showLineContextMenu(QPoint point, QPoint globalPosition) override;
    void showItemContextMenu(QPoint point, QPoint globalPosition) override;

public:
    explicit CanvasWidget(PropertiesHolder *propertiesHolder);

public:
    void newCircuitView();

private:
    QPen meshPen;
    QPen itemPen;
    QPen linePen;
    QPen endPointPen;
    QPen selectedPen;

    QBrush meshBrush;
    QBrush endPointBrush;
    QBrush resistanceBrush;
    QBrush capacitorBrush;
    QBrush inductorBrush;
    QBrush sourceBrush;
    QBrush backgroundBrush;
    QBrush selectedBrush;

};


#endif //CIRCUIT_PAINTERWIDGET_H
