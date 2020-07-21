// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ShapeView.h"

#include <QtGui/QMouseEvent>

ShapeView::ShapeView(QWidget *parent) : QGraphicsView(parent) {
  setMouseTracking(true);
  setAttribute(Qt::WA_TranslucentBackground);
  setStyleSheet("background: transparent; border: 0px");
  setWindowFlags(Qt::FramelessWindowHint);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  flipView(false, true);
}

ShapeView::~ShapeView() {}

void ShapeView::flipView(bool x_flip, bool y_flip) {
  QMatrix matrix;
  setMatrix(matrix.scale(x_flip ? -1 : 1, y_flip ? -1 : 1), true);
}

void ShapeView::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);
  event->ignore();
}
