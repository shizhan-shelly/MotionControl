// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Widgets/monitor/pps/hyper/PowermaxMonitorWidget.h"

#include "ui_PowermaxMonitorWidget.h"

PowermaxMonitorWidget::PowermaxMonitorWidget(QWidget *parent)
    : QWidget(parent)
    , station_id_(0) {

  ui_ = new Ui::PowermaxMonitorWidget();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

}

PowermaxMonitorWidget::~PowermaxMonitorWidget() {
  delete ui_;
}

void PowermaxMonitorWidget::setCurrentStation(int station_id) {
  station_id_ = station_id;
}

void PowermaxMonitorWidget::Update() {
}
