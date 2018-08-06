// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../listwidget/BaseListWidgetItem.h"

#include <QtGui/QListWidget>

namespace widget {

BaseListWidgetItem::BaseListWidgetItem(QListWidget *parent)
    : QListWidgetItem(parent) {}

BaseListWidgetItem::~BaseListWidgetItem() {}

//void SetCurrentItem(const QImage &icon) {
//  QImage source_image = QImage((const unsigned char *)rgb.data,
//                               rgb.cols,
//                               rgb.rows,
//                               rgb.step,
//                               QImage::Format_RGB888);
//
//  source_image = source_image.scaled(400, 300, Qt::KeepAspectRatio);
//  QPainter painter(&source_image);
//  painter.drawImage(0, 0,
//      QImage(":/imagewidget/resource/edit.png").scaled(source_image.width(),
//      source_image.height(), Qt::KeepAspectRatio));
//
//  setIcon(QIcon(QPixmap::fromImage(source_image)));
//}

} // namespace widget
