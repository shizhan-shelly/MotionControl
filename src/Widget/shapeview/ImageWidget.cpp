// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ImageWidget.h"

#include <QtGui/QLabel>
#include <QtGui/QPainter>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent) {
  label_ = new QLabel(this);
  label_->resize(100, 100);
  zoom_in_button_ = new QPushButton(tr("Zoom in"), this);
  zoom_out_button_ = new QPushButton(tr("Zoom out"), this);
  connect(zoom_in_button_, SIGNAL(clicked()), this, SLOT(onZoomInClicked()));
  connect(zoom_out_button_, SIGNAL(clicked()), this, SLOT(onZoomOutClicked()));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label_);
  layout->addWidget(zoom_in_button_);
  layout->addWidget(zoom_out_button_);
  setLayout(layout);
}

ImageWidget::~ImageWidget() {}

void ImageWidget::setImage() {
  update();
}

void ImageWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.drawText(100, 100, "Hello qt!");
  //painter.drawImage(0, 0, QImage(":/ShapeMonitor/Resources/Center A.bmp"));
  painter.drawImage(0, 0, QImage(":/ShapeMonitor/Resources/edit.png"));
}

void ImageWidget::onDisplay(const QPointF &pos) {
  label_->setAlignment(Qt::AlignCenter);
  label_->setText(
      QString::number(pos.x(), 'f', 2) + "  " +
      QString::number(pos.y(), 'f', 2));

}

void ImageWidget::onZoomInClicked() {
  emit scaled(2.);
}

void ImageWidget::onZoomOutClicked() {
  emit scaled(0.5);
}
