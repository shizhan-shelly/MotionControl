// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CircleWidget.h"

#include <QtGui/QPainter>

const QColor CircleWidget::PROC_COLOR_ = QColor(Qt::blue);

CircleWidget::CircleWidget(QWidget *parent) : QWidget(parent) {
  show();
}

CircleWidget::~CircleWidget() {}

void CircleWidget::clearAll() {
  position_.clear();
  radius_.clear();
  update();
}

void CircleWidget::onPunched(QPointF &pos, double radius) {
  position_.push_back(pos);
  radius_.push_back(radius);
  update();
}

void CircleWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setBrush(PROC_COLOR_);
  //painter.setViewport(QRect(0, 0, width(), height()));
  for (int i = 0; i < position_.count(); ++i) {
    painter.drawEllipse(position_[i], radius_[i], radius_[i]);
  }
}
