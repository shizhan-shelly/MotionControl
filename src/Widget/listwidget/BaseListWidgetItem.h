// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_LISTWIDGET_BASELISTWIDGETITEM_H__
#define WIDGET_LISTWIDGET_BASELISTWIDGETITEM_H__

#include <QtGui/QListWidgetItem>

class QListWidget;

namespace widget {

class BaseListWidgetItem : public QListWidgetItem {
 public:
  explicit BaseListWidgetItem(QListWidget *parent = NULL);
  virtual ~BaseListWidgetItem();

  //void SetCurrentItem(const QImage &icon);

}; // class BaseListWidgetItem

} // namespace widget

#endif // WIDGET_LISTWIDGET_BASELISTWIDGETITEM_H__
