//
// Created by bytedance on 2022/1/3.
//

#include "ItemView.h"


ItemView::ItemView(const QPoint &point) : point(point) {}

ItemView::ItemView() {}

const QPoint &ItemView::getPoint() const {
    return point;
}

void ItemView::setPoint(const QPoint &point) {
    ItemView::point = point;
}
