//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_STATE_H
#define CIRCUIT_STATE_H

#include <qlogging.h>
#include <QtCore/qpoint.h>
#include <QList>
#include "../views/CircuitView.h"
#include "../items/Resistance.h"
#include "../items/Capacitor.h"
#include "../items/Source.h"
#include "../items/Inductor.h"

enum StateType {
    None,
    DrawingLine,
    SetEndPoint,
    SetZeroEndPoint,
    SetResistance,
    SetCapacitor,
    SetInductor,
    SetSource,
    Selected,
};

class StateHolder {
public:
    virtual void changeState(StateType stateType) = 0;
    virtual bool setSelectedItems(QPoint p) = 0;
    virtual void showLineContextMenu(QPoint p, QPoint globalPosition) = 0;
    virtual void showItemContextMenu(QPoint p, QPoint globalPosition) = 0;
};

class Strategy {
protected:
    StateHolder *stateHolder;
    CircuitView *circuitView;
public:
    Strategy(StateHolder *stateHolder, CircuitView *circuitView) : stateHolder(stateHolder), circuitView(circuitView) {}
    virtual void onCellClicked(QPoint point) = 0;
    virtual QString getName() = 0;
    virtual void onCellClickedRightButton(QPoint p, QPoint globalPosition) {}
    virtual void onEnteringState(QPoint p) {}
};

class DrawingLineState : public Strategy {
protected:
    QList<QPoint> points;
    VoltagePointView *from = nullptr;
    VoltagePointView *to = nullptr;
    void clearAndGoBack();
public:
    DrawingLineState(StateHolder *stateHolder, CircuitView *circuitView) : Strategy(stateHolder, circuitView) {}
    void onCellClicked(QPoint point) override;
    QString getName() override { return "Drawing line"; }
};

class SetItemState : public Strategy {
private:
    CircuitItem *item;
public:
    SetItemState(StateHolder *stateHolder, CircuitView *circuitView, CircuitItem *item) : Strategy(stateHolder, circuitView), item(item) {}
    void onCellClicked(QPoint point) override;
};

class SetEndPointState : public Strategy {
public:
    SetEndPointState(StateHolder *stateHolder, CircuitView *circuitView)
    : Strategy(stateHolder, circuitView) {}
    void onCellClicked(QPoint point) override;
    QString getName() override { return "Setting end point"; }
};

class SetResistanceState : public SetItemState {
public:
    SetResistanceState(StateHolder *stateHolder, CircuitView *circuitView)
    : SetItemState(stateHolder, circuitView, new Resistance(0, Circuit::getNextLabel())) {}
    QString getName() override { return "Setting resistance"; }
};

class SetCapacitorState : public SetItemState {
public:
    SetCapacitorState(StateHolder *stateHolder, CircuitView *circuitView)
    : SetItemState(stateHolder, circuitView, new Capacitor(0, Circuit::getNextLabel())) {}
    QString getName() override { return "Setting capacitor"; }
};

class SetSourceState : public SetItemState {
public:
    SetSourceState(StateHolder *stateHolder, CircuitView *circuitView)
    : SetItemState(stateHolder, circuitView, new Source(0, Circuit::getNextLabel())) {}
    QString getName() override { return "Setting source"; }
};

class SetInductorState : public SetItemState {
public:
    SetInductorState(StateHolder *stateHolder, CircuitView *circuitView)
    : SetItemState(stateHolder, circuitView, new Inductor(0, Circuit::getNextLabel())) {}
    QString getName() override { return "Setting inductor"; }
};

class NoneState : public Strategy {
public:
    NoneState(StateHolder *stateHolder, CircuitView *circuitView) : Strategy(stateHolder, circuitView) {}
    void onCellClicked(QPoint point) override;
    QString getName() override { return "None"; }
};

class SelectedState : public Strategy {
private:
    ItemView *view;
public:
    SelectedState(StateHolder *stateHolder, CircuitView *circuitView) : Strategy(stateHolder, circuitView) {}
    void onCellClicked(QPoint point) override;
    void setView(ItemView *view);
    void onEnteringState(QPoint p) override;
    void onCellClickedRightButton(QPoint p, QPoint globalPosition) override;
    QString getName() override { return "CircuitItem selected"; }
};

class SetZeroEndPointState : public Strategy {
public:
    SetZeroEndPointState(StateHolder *stateHolder, CircuitView *circuitView)
            : Strategy(stateHolder, circuitView) {}
    void onCellClicked(QPoint point) override;
    QString getName() override { return "Setting zero end point"; }
};



#endif //CIRCUIT_STATE_H
