// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_LISTWIDGET_ICONLISTWIDGET_H__
#define WIDGET_LISTWIDGET_ICONLISTWIDGET_H__

#include "../listwidget/BaseListWidget.h"

namespace widget {

/**
 * @brief class IconListWidget inherits from BaseListWidget.
 *
 * This list widget will display icons in the view and set the view mode
 * as icon mode.
 */
class IconListWidget : public BaseListWidget {
  Q_OBJECT

 public:
  explicit IconListWidget(QWidget *parent = NULL);
  virtual ~IconListWidget();

}; // class IconListWidget

} // namespace widget

#endif // WIDGET_LISTWIDGET_ICONLISTWIDGET_H__
