// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_BASEWIDGET_BASEWIDGET_H__
#define WIDGET_BASEWIDGET_BASEWIDGET_H__

#include <QtGui/QWidget>

namespace widget {

/**
 * BaseWidget is a base class, the following new widget class will inherit from it.
 */
class BaseWidget : public QWidget {
  Q_OBJECT

 public:
  /**
   * FunctionName: BaseWidget(QWidget *parent)
   * Description:
   * This function will be added some contents in it.
   * For exmaple: set the uniform color and size of widget.
   * @param [in] parent: a pointer points to an object of QWidget class
   */
  explicit BaseWidget(QWidget *parent = NULL);

  /**
   * FunctionName: ~BaseWidget()
   * Description:
   * you can delete some pointers in heap
   */
  virtual ~BaseWidget();

}; // class BaseWidget

} // namespace widget

#endif  // WIDGET_BASEWIDGET_BASEWIDGET_H__
