// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../listwidget/BaseListWidgetItem.h"

#include <QtGui/QListWidget>
#include <QtGui/QPainter>

namespace widget {

static const QString SELECT_FLAG = ":/Widget/resource/edit.png";

BaseListWidgetItem::BaseListWidgetItem(QListWidget *parent)
    : QListWidgetItem(parent) {}

BaseListWidgetItem::~BaseListWidgetItem() {}

void BaseListWidgetItem::setIconScaled(const QString &res_path,
                                       int width, int height) {

  origin_path_ = res_path;
  width_ = width;
  height_ = height;
  QPixmap pixmap(origin_path_);
  //use pixmap.load(origin_path_) to judge picture is loadable.
  setIcon(QIcon(pixmap.scaled(width_, height_, Qt::KeepAspectRatio)));
}

void BaseListWidgetItem::SetSelectedFlag(bool selected) {
  QImage source_image = QImage(origin_path_);
  source_image = source_image.scaled(width_, height_, Qt::KeepAspectRatio);
  if (selected) {
    QPainter painter(&source_image);
    painter.drawImage(0, 0,
        QImage(SELECT_FLAG).scaled(source_image.width(),
        source_image.height(), Qt::KeepAspectRatio));

  }

  setIcon(QIcon(QPixmap::fromImage(source_image)));
}

} // namespace widget
