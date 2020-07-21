// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/devicediagnose/pps/kjellberg/DigitalInputWidget.h"

#include "cutter/OCutter.h"
#include "cutter/page/iowidget/iomonitoritem.h"
#include "nmlclient/NmlClient.h"

namespace cutter {

DigitalInputWidget::DigitalInputWidget(QWidget *parent)
    : IODiagnoseWidget(parent) {}

DigitalInputWidget::~DigitalInputWidget() {}

void DigitalInputWidget::Update() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  std::vector<unsigned char> input;
  input.push_back(status_pps.kjellberg_.digital_inputs_1_);
  input.push_back(status_pps.kjellberg_.digital_inputs_2_);
  for (size_t i = 0; i < input.size(); i++) {
    for (size_t j = 0; j < 8; j++) {
      bool status = input[i] & (0x01 << j);
      monitor_items_[i][j]->SetIOState(status);
    }
  }
}

void DigitalInputWidget::setCurrentStation(int station_id) {
  station_id_ = station_id;
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  unsigned short ps_device_type = status_pps.kjellberg_.ps_device_type_;
  std::map<std::string, std::string> pps_infor;
  pps_infor.insert(std::make_pair("model",
      OCutter::GetInstance()->GetPPSInfor()->GetItemValue("PPSModel",
      std::make_pair("code", ps_device_type), "model")));

  QVector<QVector<QString> > infor;
  infor << OCutter::GetInstance()->GetPPSInfor()->GetItemValues("DigitalInput1", pps_infor, "Name");
  infor << OCutter::GetInstance()->GetPPSInfor()->GetItemValues("DigitalInput2", pps_infor, "Name");
  setupPanel(infor);
}

} // namespace cutter
