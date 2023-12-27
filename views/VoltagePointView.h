//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_ENDPOINTVIEW_H
#define CIRCUIT_ENDPOINTVIEW_H


#include "ItemView.h"
#include "../items/VoltagePoint.h"

class VoltagePointView : public ItemView {
private:
    VoltagePoint *endPoint;
public:
    VoltagePointView(VoltagePoint *endPoint, QPoint point) : ItemView(point), endPoint(endPoint) {}

    VoltagePoint *getEndPoint() const;

    void setEndPoint(VoltagePoint *endPoint);
};


#endif //CIRCUIT_ENDPOINTVIEW_H
