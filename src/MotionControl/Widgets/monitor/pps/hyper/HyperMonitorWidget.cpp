// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Widgets/monitor/pps/hyper/HyperMonitorWidget.h"

#include "ui_HyperMonitorWidget.h"

HyperMonitorWidget::HyperMonitorWidget(QWidget *parent) : QWidget(parent)
                                                        , station_id_(0) {
  ui_ = new Ui::HyperMonitorWidget();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

}

HyperMonitorWidget::~HyperMonitorWidget() {
  delete ui_;
}

void HyperMonitorWidget::setCurrentStation(int station_id) {
  station_id_ = station_id;
}

void HyperMonitorWidget::Update() {
}
