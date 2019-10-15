// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/IOMonitorWidget/PPSMonitor/PPSMonitorWidget.h"

#include "cutter/ui_PPSMonitorWidget.h"
#include "f7000param/F7000ParamElement.xml.h"

namespace cutter {

PPSMonitorWidget::PPSMonitorWidget(QWidget *parent)
    : ONotifyActionWidget(parent)
    , station_index_(0) {

  ui_ = new Ui::PPSMonitorWidget();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

  initialMonitorWidget();
}

PPSMonitorWidget::~PPSMonitorWidget() {
  delete ui_;
}

void PPSMonitorWidget::initialMonitorWidget() {
  connect(ui_->station_btn_bar_, SIGNAL(stationButtonChecked(int)),
      this, SLOT(setCurrentStation(int)));

}

void PPSMonitorWidget::setCurrentStation(int station_index) {
  station_index_ = station_index;
  parameter::F7000Element *root = parameter::F7000Element::GetInstance();
  std::string pps_vendor = root->plcconfig_->GetStationPtr(station_index_)->stationplasma_->pps_->ppsvendor_->GetValue();
  if (pps_vendor.compare("Hypertherm") == 0) {
    ui_->monitor_stack_->setCurrentWidget(ui_->hypertherm_monitor_);
    ui_->hypertherm_monitor_->setCurrentStation(station_index_);
  } else if (pps_vendor.compare("Koike") == 0) {
    ui_->monitor_stack_->setCurrentWidget(ui_->koike_monitor_);
  } else if (pps_vendor.compare("Liuhe") == 0) {
    ui_->monitor_stack_->setCurrentWidget(ui_->liuhe_monitor_);
    ui_->liuhe_monitor_->setCurrentStation(station_index_);
  } else if (pps_vendor.compare("Musk") == 0) {
    ui_->monitor_stack_->setCurrentWidget(ui_->musk_monitor_);
    ui_->musk_monitor_->setCurrentStation(station_index_);
  } else if (pps_vendor.compare("Kjellberg") == 0) {
    ui_->monitor_stack_->setCurrentWidget(ui_->kjellberg_monitor_);
  } else if (pps_vendor.compare("Thermadyne") == 0) {
    ui_->monitor_stack_->setCurrentWidget(ui_->thermadyne_monitor_);
  } else {
    ui_->monitor_stack_->setCurrentWidget(ui_->none_monitor_);
  }
}

void PPSMonitorWidget::Update() {
  parameter::F7000Element *root = parameter::F7000Element::GetInstance();
  std::string pps_vendor = root->plcconfig_->GetStationPtr(station_index_)->stationplasma_->pps_->ppsvendor_->GetValue();
  if (pps_vendor.compare("Musk") == 0) {
    ui_->musk_monitor_->Update();
  } else if (pps_vendor.compare("Hypertherm") == 0) {
    ui_->hypertherm_monitor_->Update();
  } else if (pps_vendor.compare("Liuhe") == 0) {
    ui_->liuhe_monitor_->Update();
  }
}

} // namespace cutter

