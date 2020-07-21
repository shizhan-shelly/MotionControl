// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_SHAPEVIEW_H__
#define CHARGEWIDGET_SHAPEVIEW_H__

#include <QtGui/QGraphicsView>

class QMouseEvent;

/**
 * ShapeView inherits from QGraphicsView and is designed for showing custom
 * shape items. This view's background will be transparent for its parent
 * widget. By default, the View's +y direction is upward and +x direction is
 * rightward.
 */
class ShapeView : public QGraphicsView {
  Q_OBJECT

 public:
  explicit ShapeView(QWidget *parent = NULL);
  ~ShapeView();

  /**
   * FunctionName: flipView()
   * Description:
   * This function will flip the view on the x direction or on the y direction.
   * @param [in]: x_flip, whether the view will be flip on x direction.
   * @param [in]: y_flip, whether the view will be flip on y direction.
   */
  void flipView(bool x_flip, bool y_flip);

 protected:
  void mouseMoveEvent(QMouseEvent *event);

}; // class ShapeView

#endif  // CHARGEWIDGET_SHAPEVIEW_H__
