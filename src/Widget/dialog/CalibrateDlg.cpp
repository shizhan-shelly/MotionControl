// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../dialog/CalibrateDlg.h"

#include "../customwidget/CalibrateWidget.h"

namespace widget {

CalibrateDlg::CalibrateDlg(QWidget *parent)
    : widget::BaseDialog(parent) {

  widget_ = new CalibrateWidget(this);
  widget_->setMinimumSize(400, 300);
  ui_->stack_widget_->addWidget(widget_);
  ui_->stack_widget_->setCurrentWidget(widget_);
}

CalibrateDlg::~CalibrateDlg() {
  if (widget_) {
    delete widget_;
    widget_ = NULL;
  }
}

double CalibrateDlg::factor() const {
  return widget_->factor();
}

double CalibrateDlg::base() const {
  return widget_->base();
}

} // namespace widget
