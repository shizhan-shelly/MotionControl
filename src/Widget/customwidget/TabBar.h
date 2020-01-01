// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_CUSTOMWIDGET_TABBAR_H__
#define WIDGET_CUSTOMWIDGET_TABBAR_H__

#include <QtCore/QMap>
#include <QtGui/QTabBar>

namespace widget {

class TabBar : public QTabBar {
  Q_OBJECT

 public:
  explicit TabBar(QWidget *parent = NULL);
  virtual ~TabBar();

  void initBar(const QMap<int, QString> &bar_infor);

 private:
  void clearBar();

}; // class TabBar

} // namespace widget

#endif // WIDGET_CUSTOMWIDGET_TABBAR_H__
