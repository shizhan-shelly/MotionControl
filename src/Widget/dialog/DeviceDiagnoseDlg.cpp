// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../dialog/DeviceDiagnoseDlg.h"

#include <assert.h>

#include "../diagnose/DeviceDiagnoseWidget.h"

namespace widget {

DeviceDiagnoseDlg::DeviceDiagnoseDlg(QWidget *parent)
    : widget::BaseDialog(parent) {

  update_timer_.setInterval(500);

  // connect signal and slot.
}

DeviceDiagnoseDlg::~DeviceDiagnoseDlg() {
  if (widget_) {
    delete widget_;
    widget_ = NULL;
  }
}

void DeviceDiagnoseDlg::setDiagnoseWidget(DeviceDiagnoseWidget *widget) {
  assert(widget);
  widget_ = widget;
  widget_->setMinimumSize(600, 600);
  connect(&update_timer_, SIGNAL(timeout()), widget_, SLOT(Update()));
  ui_->stack_widget_->addWidget(widget_);
  ui_->stack_widget_->setCurrentWidget(widget_);
}

} // namespace widget
