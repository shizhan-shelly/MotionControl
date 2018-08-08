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

  /// Set item's icon with special scale of (width, height).
  void setIconScaled(const QString &res_path, int width, int height);

  // If this item is selected, draw a special flag on the icon of it;
  // otherwise, revert to the origin icon.
  void SetSelectedFlag(bool selected);

 private:
  QString origin_path_;
  int width_;
  int height_;

}; // class BaseListWidgetItem

} // namespace widget

#endif // WIDGET_LISTWIDGET_BASELISTWIDGETITEM_H__
