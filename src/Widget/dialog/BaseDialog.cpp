// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../dialog/BaseDialog.h"

namespace widget {

BaseDialog::BaseDialog(QWidget *parent) : QDialog(parent) {
  ui_ = new Ui::BaseDialog;
  ui_->setupUi(this);
}

BaseDialog::~BaseDialog() {
  delete ui_;
}


} // namespace widget
