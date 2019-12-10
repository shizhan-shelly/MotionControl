// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "IOMonitorItem.h"

#include <assert.h>

#include "ui_IOMonitorItem.h"

static const QString OPEN_ICON = ":/Widget/resource/open.png";
static const QString CLOSE_ICON = ":/Widget/resource/closed.png";

namespace widget {

IOMonitorItem::IOMonitorItem(QWidget *parent) : QWidget(parent)
                                              , selected_(false)
                                              , index_(0) {
  ui_ = new Ui::IOMonitorItem;
  ui_->setupUi(this);
}

IOMonitorItem::~IOMonitorItem() {}

void IOMonitorItem::setup(const QString &description, int index) {
  assert(!description.isEmpty());
  ui_->description_->setText(description);
  index_ = index;
}

void IOMonitorItem::Update(bool status) {
  ui_->status_->setPixmap(status ? QPixmap(OPEN_ICON) : QPixmap(CLOSE_ICON));
}

void IOMonitorItem::focusOutEvent(QFocusEvent *event) {
  selected_ = false;
  setStyleSheet(0);
  event->accept();
}

void IOMonitorItem::focusInEvent(QFocusEvent *event) {
  setFocus();
  selected_ = true;
  setStyleSheet("QLabel{background-color: grey}");
  event->accept();
}

void IOMonitorItem::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    emit selected(index_);
  }
}

} // namespace widget
