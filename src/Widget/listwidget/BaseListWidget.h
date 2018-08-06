// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_LISTWIDGET_BASELISTWIDGET_H__
#define WIDGET_LISTWIDGET_BASELISTWIDGET_H__

#include <QtGui/QListWidget>

namespace widget {

class BaseListWidget : public QListWidget {
  Q_OBJECT

 public:
  explicit BaseListWidget(QWidget *parent = NULL);
  virtual ~BaseListWidget();

}; // class BaseListWidget

} // namespace widget

#endif // WIDGET_LISTWIDGET_BASELISTWIDGET_H__
