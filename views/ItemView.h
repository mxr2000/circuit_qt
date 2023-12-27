//
// Created by bytedance on 2022/1/3.
//

#ifndef CIRCUIT_VIEW_H
#define CIRCUIT_VIEW_H


#include <QtCore/qpoint.h>

class ItemView {
private:
    QPoint point;
public:
    const QPoint &getPoint() const;

    void setPoint(const QPoint &point);

    ItemView();

    ItemView(const QPoint &point);
};


#endif //CIRCUIT_VIEW_H
