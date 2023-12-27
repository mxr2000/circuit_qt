//
// Created by bytedance on 2022/1/3.
//

#include "VoltagePointView.h"

VoltagePoint *VoltagePointView::getEndPoint() const {
    return endPoint;
}

void VoltagePointView::setEndPoint(VoltagePoint *endPoint) {
    VoltagePointView::endPoint = endPoint;
}
