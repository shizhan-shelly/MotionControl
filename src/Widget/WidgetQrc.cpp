// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: miaochengyu@fLcnc.com (Miaocheng Yu)

#include "WidgetQrc.h"

#include <QtCore/QDir>

WidgetQrc::WidgetQrc() {
  Q_INIT_RESOURCE(Widget);
}

WidgetQrc::~WidgetQrc() {
  Q_CLEANUP_RESOURCE(Widget);
}
