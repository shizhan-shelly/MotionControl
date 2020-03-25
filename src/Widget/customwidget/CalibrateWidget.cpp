// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CalibrateWidget.h"

#include "ui_CalibrateWidget.h"

namespace widget {

CalibrateWidget::CalibrateWidget(QWidget *parent)
  : QWidget(parent)
  , factor_(1.0)
  , base_(0.0) {

  ui_ = new Ui::CalibrateWidget();
  ui_->setupUi(this);

  connect(ui_->calculate_btn_, SIGNAL(clicked()), this, SLOT(onCalculate()));
}

CalibrateWidget::~CalibrateWidget() {
  delete ui_;
}

void CalibrateWidget::onCalculate() {
  double exc_value1 = ui_->exp_value1_->text().toDouble();
  double exc_value2 = ui_->exp_value2_->text().toDouble();
  double act_value1 = ui_->act_value1_->text().toDouble();
  double act_value2 = ui_->act_value2_->text().toDouble();
  if (exc_value1 != exc_value2) {
    factor_ = (act_value1 - act_value2) / (exc_value1 - exc_value2);
    base_ = (act_value2 * exc_value1 - act_value1 * exc_value2) / (exc_value1 - exc_value2);
  }
}

} // namespace widget
