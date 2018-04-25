// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef SYSTEMCONFIGWIDGET_H
#define SYSTEMCONFIGWIDGET_H

#include "../../Widget/basewidget/BaseWidget.h"

namespace Ui {
  class SystemConfigWidgetForm;
}

class SystemConfigModel;

class SystemConfigWidget : public ::widget::BaseWidget {
  Q_OBJECT

 public:
  explicit SystemConfigWidget(QWidget *parent = NULL);
  ~SystemConfigWidget();

  void setModel(SystemConfigModel *model);

 private:
  SystemConfigModel *system_config_model_;
  Ui::SystemConfigWidgetForm *ui_;

}; // class SystemConfigWidget

#endif // SYSTEMCONFIGWIDGET_H
