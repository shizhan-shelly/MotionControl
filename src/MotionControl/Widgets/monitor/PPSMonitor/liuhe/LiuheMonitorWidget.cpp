// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/IOMonitorWidget/PPSMonitor/liuhe/LiuheMonitorWidget.h"

#include "cutter/ui_LiuheMonitorWidget.h"
#include "f7000param/F7000ParamElement.xml.h"

namespace cutter {

LiuheMonitorWidget::LiuheMonitorWidget(QWidget *parent) : QWidget(parent)
                                                        , station_id_(0) {
  ui_ = new Ui::LiuheMonitorWidget();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

}

LiuheMonitorWidget::~LiuheMonitorWidget() {
  delete ui_;
}

void LiuheMonitorWidget::setCurrentStation(int station_id) {
  station_id_ = station_id;
  parameter::F7000PPSLiuheElement *pps_liuhe =
      parameter::F7000Element::GetInstance()->plcconfig_->\
      GetStationPtr(station_id_)->stationplasma_->pps_->ppsliuhe_;

  std::string pps_model = pps_liuhe->ppsliuhetype_->GetValue();
  if (pps_model.compare("LH270A") == 0) {
    ui_->stack_->setCurrentWidget(ui_->lh270a_);
    ui_->lh270a_->setCurrentStation(station_id_);
  }
}

void LiuheMonitorWidget::Update() {
  parameter::F7000PPSLiuheElement *pps_liuhe =
      parameter::F7000Element::GetInstance()->plcconfig_->\
      GetStationPtr(station_id_)->stationplasma_->pps_->ppsliuhe_;

  std::string pps_model = pps_liuhe->ppsliuhetype_->GetValue();
  if (pps_model.compare("LH270A") == 0) {
    ui_->lh270a_->Update();
  }
}

} // namespace cutter
