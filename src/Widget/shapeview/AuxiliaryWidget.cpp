// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "AuxiliaryWidget.h"

#include <QtGui/QPainter>

const QColor AuxiliaryWidget::PROC_COLOR_ = QColor(Qt::blue);
const QColor AuxiliaryWidget::CURSOR_COLOR_ = QColor(Qt::green);
const QPointF AuxiliaryWidget::ORIGINAL_POS_ = QPointF(60.0, 60.0);

AuxiliaryWidget::AuxiliaryWidget(QWidget *parent) : QWidget(parent) {
  cursor_position_ = ORIGINAL_POS_;
  setMouseTracking(true);
}

AuxiliaryWidget::~AuxiliaryWidget() {}

void AuxiliaryWidget::clearAll() {
  circles_.clear();
  update();
}

void AuxiliaryWidget::onPunched(const QVector<QPair<QPointF, double> >
                                &circles) {

  circles_ = circles;
  update();
}

void AuxiliaryWidget::onLocated(const QPointF &pos) {
  cursor_position_ = pos;
  update();
}

void AuxiliaryWidget::onCloseToPoint(const QPoint &point, bool update_pos) {
  accurate_position_ = point;
  update_pos_ = update_pos;
  update();
}

void AuxiliaryWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setBrush(PROC_COLOR_);
  for (int i = 0; i < circles_.count(); ++i) {
    painter.drawEllipse(circles_[i].first, circles_[i].second,
        circles_[i].second);

  }

  painter.setBrush(Qt::NoBrush);
  painter.setPen(QPen(CURSOR_COLOR_));
  painter.drawEllipse(cursor_position_, 10, 10);
  painter.drawLine(QPointF(cursor_position_.x() - 15, cursor_position_.y()),
                   QPointF(cursor_position_.x() + 15, cursor_position_.y()));

  painter.drawLine(QPointF(cursor_position_.x(), cursor_position_.y() - 15),
                   QPointF(cursor_position_.x(), cursor_position_.y() + 15));

  if (update_pos_) {
    painter.setPen(QPen(QBrush(Qt::darkRed), 5));
    painter.drawPoint(accurate_position_);
  }
}
