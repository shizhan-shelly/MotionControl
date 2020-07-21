// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_CURSORVIEW_H__
#define CHARGEWIDGET_CURSORVIEW_H__

#include <QtCore/QPointF>
#include <QtGui/QGraphicsView>

class CursorItem;
class QGraphicsScene;

class CursorView : public QGraphicsView {
 public:
  CursorView();
  ~CursorView();

 public slots:
  void onLocated(QPointF &pos);

 private:
  QGraphicsScene *scene_;
  CursorItem *cursor_;

  static const QPointF ORIGINAL_POS_;

}; // class CursorView

#endif  // CHARGEWIDGET_CURSORITEM_H__
