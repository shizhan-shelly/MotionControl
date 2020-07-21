// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_CURSORITEM_H__
#define CHARGEWIDGET_CURSORITEM_H__

#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtGui/QGraphicsItem>

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

class CursorItem : public QGraphicsItem {
 public:
  CursorItem();
  ~CursorItem();

  void setCursorPos(const QPointF &pos);
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = NULL);

 private:
  QPointF position_;

}; // class CursorItem

#endif  // CHARGEWIDGET_CURSORITEM_H__
