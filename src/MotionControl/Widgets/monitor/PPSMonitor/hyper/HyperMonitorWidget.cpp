// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/IOMonitorWidget/PPSMonitor/hyper/HyperMonitorWidget.h"

#include "cutter/ui_HyperMonitorWidget.h"
#include "f7000param/F7000ParamElement.xml.h"

namespace cutter {

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
  parameter::F7000PPSHyperElement *pps_hyper =
      parameter::F7000Element::GetInstance()->plcconfig_->\
      GetStationPtr(station_id_)->stationplasma_->pps_->ppshyper_;

  std::string pps_model = pps_hyper->ppshypertype_->GetValue();
  if (pps_model.compare("Powermax") == 0) {
    ui_->stack_->setCurrentWidget(ui_->powermax_);
    ui_->powermax_->setCurrentStation(station_id_);
  } else if (pps_model.compare("HPR") == 0) {
    ui_->stack_->setCurrentWidget(ui_->hpr_);
  } else {
    ui_->stack_->setCurrentWidget(ui_->xpr_);
  }
}

void HyperMonitorWidget::Update() {
  parameter::F7000PPSHyperElement *pps_hyper =
      parameter::F7000Element::GetInstance()->plcconfig_->\
      GetStationPtr(station_id_)->stationplasma_->pps_->ppshyper_;

  std::string pps_model = pps_hyper->ppshypertype_->GetValue();
  if (pps_model.compare("Powermax") == 0) {
    ui_->powermax_->Update();
  }
}

} // namespace cutter
