//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_LINEITEM_H
#define CIRCUIT_LINEITEM_H

#include "LineView.h"
#include "../items/CircuitItem.h"

class LineView;

class LineItem : public ItemView {
private:
    CircuitItem *item;
    int offset;
public:
    LineItem(CircuitItem *item, int offset) : item(item), offset(offset) {}
    int getOffset() const { return offset; }
    void setOffset(int offset) { this->offset = offset; }
    CircuitItem* getItem() { return item; }
};


#endif //CIRCUIT_LINEITEM_H
