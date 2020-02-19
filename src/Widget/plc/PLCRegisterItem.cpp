// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "PLCRegisterItem.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

namespace widget {

PLCRegisterItem::PLCRegisterItem(QWidget *parent,
    const QString &variable_name,
    const QString &default_value,
    PLCRegisterType reg_type,
    bool read_only) : QWidget(parent)
                    , reg_type_(reg_type) {

  layout_ = new QHBoxLayout(this);
  layout_->setMargin(0);
  layout_->setSpacing(5);
  setLayout(layout_);

  register_ = new QLabel(this);
  register_->setMinimumSize(50, 20);
  register_->setText(variable_name);
  layout_->addWidget(register_);

  value_ = new QLineEdit(this);
  value_->setMinimumSize(50, 20);
  value_->setText(default_value);
  value_->setReadOnly(read_only);
  layout_->addWidget(value_);

  if (!read_only) {
    send_ = new QPushButton(this);
    send_->setMinimumSize(50, 20);
    send_->setText("");
    layout_->addWidget(send_);
    connect(send_, SIGNAL(clicked()), this, SLOT(onSend()));
  } else {
    QWidget *null = new QWidget(this);
    null->setMinimumSize(50, 20);
    layout_->addWidget(null);
  }
}

PLCRegisterItem::~PLCRegisterItem() {}

void PLCRegisterItem::Update(const QString &value) {
  value_->setText(value);
}

void PLCRegisterItem::onSend() {
  emit valueChanged(register_->text(), value_->text());
}

} // namespace widget
