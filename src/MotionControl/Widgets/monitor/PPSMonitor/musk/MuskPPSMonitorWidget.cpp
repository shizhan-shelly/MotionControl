// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/IOMonitorWidget/PPSMonitor/MuskPPSMonitorWidget.h"

#include "cutter/OCutter.h"
#include "cutter/ui_MuskPPSMonitorWidget.h"
#include "f7000param/F7000ParamElement.xml.h"

#include "device/api/PPSAPI.h"
#include "nmlclient/NmlClient.h"

namespace cutter {

MuskPPSMonitorWidget::MuskPPSMonitorWidget(QWidget *parent)
    : QWidget(parent)
    , station_index_(0) {

  ui_ = new Ui::MuskPPSMonitorWidget();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

  connect(ui_->cut_current_p_, SIGNAL(clicked()), this, SLOT(onCutCurrentAdd()));
  connect(ui_->cut_current_n_, SIGNAL(clicked()), this, SLOT(onCutCurrentSub()));
}

MuskPPSMonitorWidget::~MuskPPSMonitorWidget() {
  delete ui_;
}

void MuskPPSMonitorWidget::setCurrentStation(int station_index) {
  station_index_ = station_index;
}

void MuskPPSMonitorWidget::Update() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
                          status_->station_manager_.stations_[station_index_].
                          plasma_.pps_;

  ui_->water_pressure_->setPixmap(status_pps.status_[0] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gas_pressure_->setPixmap(status_pps.status_[1] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->power_supply_->setPixmap(status_pps.status_[2] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->cut_current_->setText(QString::number(status_pps.current_, 'f', 1));

  ui_->noload_voltage_->setText(QString::number(status_pps.noload_voltage_, 'f', 1));
}

void MuskPPSMonitorWidget::onCutCurrentAdd() {
  // control cut current by increase
  parameter::F7000Element *root = parameter::F7000Element::GetInstance();
  double current_adjust = root->plcconfig_->GetStationPtr(station_index_)->stationplasma_->pps_->ppsmusk_->ppsmuskuniversal_->currentadjust_->Get();
  double current_max = root->plcconfig_->GetStationPtr(station_index_)->stationplasma_->pps_->ppsmusk_->ppsmuskuniversal_->currentmax_->Get();
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
                          status_->station_manager_.stations_[station_index_].plasma_.pps_;

  float cur_cutting_current = status_pps.current_ + current_adjust;
  cur_cutting_current = cur_cutting_current > current_max ? current_max : cur_cutting_current;
  PPS_SetCuttingCurrent(cur_cutting_current, station_index_);
}

void MuskPPSMonitorWidget::onCutCurrentSub() {
  // control cut current by decrease
  parameter::F7000Element *root = parameter::F7000Element::GetInstance();
  double current_adjust = root->plcconfig_->GetStationPtr(station_index_)->stationplasma_->pps_->ppsmusk_->ppsmuskuniversal_->currentadjust_->Get();
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->status_->
                          station_manager_.stations_[station_index_].plasma_.pps_;

  float cur_cutting_current = status_pps.current_ - current_adjust;
  cur_cutting_current = cur_cutting_current < 0 ? 0 : cur_cutting_current;
  PPS_SetCuttingCurrent(cur_cutting_current, station_index_);
}

} // namespace cutter

