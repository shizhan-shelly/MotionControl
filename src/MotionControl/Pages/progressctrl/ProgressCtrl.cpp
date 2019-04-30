// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ProgressCtrl.h"

#include "ui_ProgressCtrl.h"

ProgressCtrl::ProgressCtrl(QWidget *parent) : QWidget(parent) {
  ui_ = new Ui::ProgressCtrlForm;
  ui_->setupUi(this);
  ui_->progress_->reset();
}

ProgressCtrl::~ProgressCtrl() {
  delete ui_;
}

void ProgressCtrl::initProgress(const QString &prompt, int whole) {
  prompt_ = prompt;
  entry_ = whole;
  ui_->progress_->setRange(0, entry_);
  ui_->progress_->setValue(0);
  ui_->tips_->setText(QString("%1\n0/%2").arg(prompt_).arg(entry_));
}

void ProgressCtrl::onProgress(int index) {
  ui_->progress_->setValue(index + 1);
  ui_->tips_->setText(QString("%1\n%2/%3").arg(prompt_)
                                          .arg(index + 1)
                                          .arg(entry_));

  qApp->processEvents();
}
