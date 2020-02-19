// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "HPRDiagnose.h"

#include "ui_HPRDiagnose.h"

namespace cutter {

HPRDiagnose::HPRDiagnose(QWidget *parent)
    : QWidget(parent)
    , station_id_(0) {

  ui_ = new Ui::HPRDiagnose();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

  initialDiagnoseWidget();
}

HPRDiagnose::~HPRDiagnose() {
  delete ui_;
}

void HPRDiagnose::initialDiagnoseWidget() {
  connect(ui_->preflow_gas_test_, SIGNAL(clicked()), this, SLOT(onPreflowGasTest()));
  connect(ui_->cutflow_gas_test_, SIGNAL(clicked()), this, SLOT(onCutflowGasTest()));
  connect(ui_->manual_pump_ctrl_, SIGNAL(clicked()), this, SLOT(onManualPumpCtrl()));
  connect(ui_->set_btn_, SIGNAL(clicked()), this, SLOT(onSetParameter()));
  connect(ui_->clear_pps_record_, SIGNAL(clicked()), this, SLOT(onClearRecord()));
}

void HPRDiagnose::setCurrentStation(int station_id) {
  station_id_ = station_id;
}

void HPRDiagnose::Update() {
}

void HPRDiagnose::onPreflowGasTest() {
}

void HPRDiagnose::onCutflowGasTest() {
}

void HPRDiagnose::onManualPumpCtrl() {
}

void HPRDiagnose::onSetParameter() {
}

void HPRDiagnose::onClearRecord() {
}

} // namespace cutter
