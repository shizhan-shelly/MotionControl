// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/devicediagnose/pps/hyper/PowermaxDiagnose.h"

#include "cutter/controller/pps/hyper/PowermaxPPSDev.h"
#include "cutter/OCutter.h"
#include "cutter/ui_PowermaxDiagnose.h"
#include "nmlclient/NmlClient.h"

namespace cutter {

PowermaxDiagnose::PowermaxDiagnose(QWidget *parent)
    : QWidget(parent)
    , station_id_(0) {

  ui_ = new Ui::PowermaxDiagnose;
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

  initialDiagnoseWidget();
}

PowermaxDiagnose::~PowermaxDiagnose() {
  delete ui_;
}

void PowermaxDiagnose::initialDiagnoseWidget() {
  connect(ui_->gas_test_button_, SIGNAL(clicked()), this, SLOT(onGasTest()));
}

void PowermaxDiagnose::setCurrentStation(int station_id) {
  station_id_ = station_id;
}

void PowermaxDiagnose::Update() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->station_manager_.stations_[station_id_].plasma_.pps_;

  unsigned short cut_mode = status_pps.hyper_.powermax_.cut_mode_;
  unsigned short arc_current = status_pps.hyper_.powermax_.arc_current_;
  unsigned short gas_pressure = status_pps.hyper_.powermax_.gas_pressure_;
  unsigned short fault_code = status_pps.hyper_.powermax_.fault_code_;
  unsigned short arc_time_low = status_pps.hyper_.powermax_.arc_time_low_;
  unsigned short arc_time_high = status_pps.hyper_.powermax_.arc_time_high_;

  ui_->arc_current_->setText(QString::number(arc_current / 64, 'f', 1));
  ui_->gas_pressure_->setText(QString::number(gas_pressure / 128, 'f', 1));
  ui_->cut_mode_->setText(PowermaxPPSDev::CutMode(cut_mode));
  ui_->torch_lead_length_->setText(PowermaxPPSDev::TorchLeadLength(status_pps.hyper_.powermax_.torch_index_));
  ui_->arc_on_time_->setText(QString::number(PowermaxPPSDev::ArcOnTime(arc_time_low, arc_time_high), 'f', 1));
  ui_->fault_code_->setText(QString::number(fault_code));
  ui_->fault_code_description_->setPlainText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "FaultCode", PowermaxPPSDev::FaultCode(fault_code), "description").c_str());
  ui_->fault_resolve_->setPlainText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "FaultCode", PowermaxPPSDev::FaultCode(fault_code), "resolve").c_str());

}

void PowermaxDiagnose::onGasTest() {
}

} // namespace cutter
