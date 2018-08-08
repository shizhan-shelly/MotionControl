// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControlQrc.h"

#include <QtCore/QDir>

MotionControlQrc::MotionControlQrc() {
  Q_INIT_RESOURCE(MotionControl);
}

MotionControlQrc::~MotionControlQrc() {
  Q_CLEANUP_RESOURCE(MotionControl);
}
