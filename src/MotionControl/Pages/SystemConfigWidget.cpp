// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SystemConfigWidget.h"

#include <assert.h>

#include "SystemConfigModel.h"
#include "ui_SystemConfigWidget.h"

SystemConfigWidget::SystemConfigWidget(QWidget *parent)
    : ::widget::BaseWidget(parent)
    , system_config_model_(NULL) {

  ui_ = new Ui::SystemConfigWidgetForm;
  ui_->setupUi(this);
}

SystemConfigWidget::~SystemConfigWidget() {
  delete ui_;
}

void SystemConfigWidget::setModel(SystemConfigModel *model) {
  assert(model);
  system_config_model_ = model;
  ui_->table_view_->setModel(model);
}
