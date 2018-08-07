// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../listwidget/BaseListWidgetItem.h"

#include <QtGui/QListWidget>
#include <QtGui/QPainter>

namespace widget {

static const QString SELECT_FLAG = ":/imagewidget/resource/edit.png";

BaseListWidgetItem::BaseListWidgetItem(QListWidget *parent)
    : QListWidgetItem(parent) {}

BaseListWidgetItem::~BaseListWidgetItem() {}

void BaseListWidgetItem::setIconScaled(const QString &res_path,
                                       int width, int height) {

  origin_path_ = res_path;
  QPixmap pixmap(origin_path_);
  setIcon(QIcon(pixmap.scaled(width, height, Qt::KeepAspectRatio)));
}

void BaseListWidgetItem::SetSelectedFlag(bool selected) {
  QImage source_image = QImage(origin_path_);
  source_image = source_image.scaled(400, 300, Qt::KeepAspectRatio);
  QPainter painter(&source_image);
  painter.drawImage(0, 0,
      QImage(SELECT_FLAG).scaled(source_image.width(),
      source_image.height(), Qt::KeepAspectRatio));

  setIcon(QIcon(QPixmap::fromImage(source_image)));
}

} // namespace widget
