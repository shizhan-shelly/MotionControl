// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CursorView.h"

#include <QtGui/QGraphicsScene>

#include "CursorItem.h"

const QPointF CursorView::ORIGINAL_POS_ = QPointF(460.0, 360.0);

CursorView::CursorView() {
  scene_ = new QGraphicsScene;
  scene_->setItemIndexMethod(QGraphicsScene::NoIndex);

  cursor_ = new CursorItem();
  cursor_->setCursorPos(ORIGINAL_POS_);
  scene_->addItem(cursor_);

  setScene(scene_);
  setAttribute(Qt::WA_TranslucentBackground);
  setStyleSheet("background: transparent; border: 0px");
  setWindowFlags(Qt::FramelessWindowHint);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  show();
}

CursorView::~CursorView() {}

void CursorView::onLocated(QPointF &pos) {
  cursor_->setCursorPos(pos);
}
