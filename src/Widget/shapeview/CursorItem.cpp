// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CursorItem.h"

#include <QtGui/QPainter>
#include <QtGui/QStyleOptionGraphicsItem>
#include <QtGui/QWidget>

CursorItem::CursorItem() {
}

CursorItem::~CursorItem() {
}

void CursorItem::setCursorPos(const QPointF &pos) {
  position_ = pos;
}

QRectF CursorItem::boundingRect() const {
  return QRectF(0, 0, 1000, 1000);
}

void CursorItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {

  painter->setPen(QPen(Qt::green));
  painter->drawEllipse(position_, 40, 40);
  painter->drawLine(QPointF(position_.x() - 60, position_.y()),
                    QPointF(position_.x() + 60, position_.y()));

  painter->drawLine(QPointF(position_.x(), position_.y() - 60),
                    QPointF(position_.x(), position_.y() + 60));

}
