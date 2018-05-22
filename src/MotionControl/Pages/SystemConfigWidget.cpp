// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SystemConfigWidget.h"

#include <assert.h>

#include "SystemConfigItem.h"
#include "SystemConfigModel.h"
#include "ui_SystemConfigWidget.h"

SystemConfigWidget::SystemConfigWidget(QWidget *parent)
    : ::widget::BaseWidget(parent)
    , system_config_model_(NULL) {

  ui_ = new Ui::SystemConfigWidgetForm;
  ui_->setupUi(this);
  connect(ui_->filter_view_,
      SIGNAL(systemConfigRecord(std::vector<std::vector<std::pair<std::string, std::string> > >)),
      this,
      SLOT(UpdateSystemConfigModel(std::vector<std::vector<std::pair<std::string, std::string> > >)));

}

SystemConfigWidget::~SystemConfigWidget() {
  delete ui_;
}

void SystemConfigWidget::setModel(SystemConfigModel *model) {
  assert(model);
  system_config_model_ = model;
  ui_->table_view_->setModel(model);
}

void SystemConfigWidget::UpdateSystemConfigModel(
    const std::vector<std::vector<std::pair<std::string, std::string> > > &records) {

  system_config_model_->clear();
  for (size_t i = 0; i < records.size(); i++) {
    SystemConfigItem *item = new SystemConfigItem();
    for (size_t j = 0; j < records[i].size(); j++) {
      item->Append(records[i][j].second);
    }
    system_config_model_->insertRecord(system_config_model_->rowCount(), item);
  }
}
