// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PAGES_CONSUMABLESWIDGET_H__
#define PAGES_CONSUMABLESWIDGET_H__

#include "Widget/basewidget/BaseWidget.h"

namespace Ui {
  class ConsumablesWidgetForm;
}

namespace widget {
  class BaseListWidgetItem;
}

class ConsumablesWidget : public ::widget::BaseWidget {
  Q_OBJECT

 public:
  explicit ConsumablesWidget(QWidget *parent = NULL);
  ~ConsumablesWidget();

  void showConsumables(const QVector<QPair<QString, QString> > &onsumables);

 private:
  QList<widget::BaseListWidgetItem *> icon_items_;
  Ui::ConsumablesWidgetForm *ui_;

  void clearAll();

}; // class ConsumablesWidget

#endif // PAGES_CONSUMABLESWIDGET_H__
