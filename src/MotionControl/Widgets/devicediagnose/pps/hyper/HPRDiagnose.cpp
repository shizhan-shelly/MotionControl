// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "HPRDiagnose.h"

//#include "cutter/controller/pps/hyper/HPRPPSDev.h"
#include "MotionControl/Cutter.h"
#include "ui_HPRDiagnose.h"
//#include "cutter/widget/specialdialog/ErrorNotifyDlg.h"
//#include "device/pps/hyper/HPRDefine.h"
//#include "nmlclient/NmlClient.h"
//#include "widget/dialog/ConfirmDlg.h"

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
  //ui_->plasma_statistics_widget_->setCutType(Plasma);

  connect(ui_->preflow_gas_test_, SIGNAL(clicked()), this, SLOT(onPreflowGasTest()));
  connect(ui_->cutflow_gas_test_, SIGNAL(clicked()), this, SLOT(onCutflowGasTest()));
  connect(ui_->manual_pump_ctrl_, SIGNAL(clicked()), this, SLOT(onManualPumpCtrl()));
  connect(ui_->system_reset_, SIGNAL(clicked()), this, SLOT(onSystemReset()));
  connect(ui_->set_btn_, SIGNAL(clicked()), this, SLOT(onSetParameter()));
  connect(ui_->fault_code_infor_, SIGNAL(clicked()), this, SLOT(onErrorCode()));
  connect(ui_->clear_pps_record_, SIGNAL(clicked()), this, SLOT(onClearRecord()));
}

void HPRDiagnose::setCurrentStation(int station_id) {
  station_id_ = station_id;
  /// HPR device parameter
  //ui_->hpr_device_config_->setCurrentStation(station_id_);
  /// plasma statistic parameter
  //OCuttingService *service = OCuttingService::GetInstance();
  //service->GetOStatisticsParam()->UpdateDisplayValue();
}

void HPRDiagnose::Update() {
  //if (OCutter::GetInstance()->GetController()->dev_comm_->status_ == NULL) {
  //  return;
  //}
  //Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //    status_->plasma_[station_id_].pps_;

  //std::string pps_firmware_version = status_pps.hyper_.hpr_.pps_firmware_version_;
  //std::string gc_firmware_version = status_pps.hyper_.hpr_.gc_firmware_version_;
  //unsigned short current_setpoint = status_pps.hyper_.hpr_.current_setpoint_;
  //unsigned short plasma_gas_type = status_pps.hyper_.hpr_.plasma_gas_type_;
  //unsigned short shield_gas_type = status_pps.hyper_.hpr_.shield_gas_type_;
  //unsigned short plasma_gas_preflow = status_pps.hyper_.hpr_.plasma_gas_preflow_;
  //unsigned short plasma_gas_cutflow = status_pps.hyper_.hpr_.plasma_gas_cutflow_;
  //unsigned short shield_gas_preflow = status_pps.hyper_.hpr_.shield_gas_preflow_;
  //unsigned short shield_gas_cutflow = status_pps.hyper_.hpr_.shield_gas_cutflow_;
  //unsigned short cut_gas_1_pressure = status_pps.hyper_.hpr_.cut_gas_1_pressure_;
  //unsigned short cut_gas_2_pressure = status_pps.hyper_.hpr_.cut_gas_2_pressure_;

  //unsigned short pps_state_code = status_pps.hyper_.hpr_.pps_state_code_;
  //unsigned short pps_fault_code = status_pps.hyper_.hpr_.pps_fault_code_;
  //unsigned short line_voltage = status_pps.hyper_.hpr_.line_voltage_;
  //unsigned short coolant_flow = status_pps.hyper_.hpr_.coolant_flow_;
  //unsigned short chopper_A_current = status_pps.hyper_.hpr_.chopper_A_current_;
  //unsigned short chopper_B_current = status_pps.hyper_.hpr_.chopper_B_current_;
  //unsigned short work_current = status_pps.hyper_.hpr_.work_current_;
  //unsigned short transformer_temperature = status_pps.hyper_.hpr_.transformer_temperature_;
  //unsigned short chopper_A_temperature = status_pps.hyper_.hpr_.chopper_A_temperature_;
  //unsigned short chopper_B_temperature = status_pps.hyper_.hpr_.chopper_B_temperature_;
  //unsigned short coolant_temperature = status_pps.hyper_.hpr_.coolant_temperature_;

  //ui_->pps_version_->setText(pps_firmware_version.c_str());
  //ui_->gc_version_->setText(gc_firmware_version.c_str());
  //ui_->current_setpoint_->setText(QString::number(current_setpoint));
  //ui_->plasma_gas_cutflow_->setText(QString::number(plasma_gas_cutflow));
  //ui_->plasma_gas_preflow_->setText(QString::number(plasma_gas_preflow));
  //ui_->shield_gas_cutflow_->setText(QString::number(shield_gas_cutflow));
  //ui_->shield_gas_preflow_->setText(QString::number(shield_gas_preflow));
  //ui_->cut_gas1_gas_pressure_->setText(QString::number(cut_gas_1_pressure));
  //ui_->cut_gas2_gas_pressure_->setText(QString::number(cut_gas_2_pressure));
  //ui_->pps_status_code_->setText(QString::number(pps_state_code));
  //ui_->pps_fault_code_->setText(QString::number(pps_fault_code));
  //ui_->line_voltage_->setText(QString::number(line_voltage / 10., 'f', 1));
  //ui_->coolant_flow_->setText(QString::number(coolant_flow / 100., 'f', 2));
  //ui_->chopper_A_current_->setText(QString::number(chopper_A_current));
  //ui_->chopper_B_current_->setText(QString::number(chopper_B_current));
  //ui_->work_current_->setText(QString::number(work_current));
  //ui_->plasma_gas_type_->setText(OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
  //    "GasType", std::make_pair("code", plasma_gas_type), "type").c_str());

  //ui_->shield_gas_type_->setText(OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
  //    "GasType", std::make_pair("code", shield_gas_type), "type").c_str());

  //std::map<std::string, std::string> temperature_infor;
  //temperature_infor.insert(std::make_pair("model", "USP12355"));
  //ui_->transformer_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "Temperature", temperature_infor, std::make_pair("ResistanceRatio",
  //    HPRPPSDev::CalcAD(transformer_temperature)), "Celsius", 0.05).c_str());

  //ui_->chopper_A_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "Temperature", temperature_infor, std::make_pair("ResistanceRatio",
  //    HPRPPSDev::CalcAD(chopper_A_temperature)), "Celsius", 0.05).c_str());

  //ui_->chopper_B_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "Temperature", temperature_infor, std::make_pair("ResistanceRatio",
  //    HPRPPSDev::CalcAD(chopper_B_temperature)), "Celsius", 0.05).c_str());

  //ui_->coolant_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "Temperature", temperature_infor, std::make_pair("ResistanceRatio",
  //    HPRPPSDev::CalcAD(coolant_temperature)), "Celsius", 0.05).c_str());

  //ui_->corner_signal_->setText(status_pps.hyper_.hpr_.pps_input_[6] == '1' ?
  //    tr("ON") : tr("OFF"));

  //if (pps_fault_code > 0) {
  //  ui_->pps_fault_code_->setStyleSheet("background-color: rgb(255, 0, 0);");
  //} else {
  //  ui_->pps_fault_code_->setStyleSheet("");
  //}
}

void HPRDiagnose::onPreflowGasTest() {
  static bool gas_test_on = true;
  //HPRPPSDev::Question(station_id_,
  //    gas_test_on ? GAS_PREFLOW_TEST_START : GAS_PREFLOW_TEST_STOP);

  ui_->preflow_gas_test_->setStyleSheet(
      gas_test_on ? "background: rgb(0, 255, 0)" : "background: rgb(255, 0, 0)");

  gas_test_on = !gas_test_on;
}

void HPRDiagnose::onCutflowGasTest() {
  static bool gas_test_on = true;
  //HPRPPSDev::Question(station_id_,
  //    gas_test_on ? GAS_CUTFLOW_TEST_START : GAS_CUTFLOW_TEST_STOP);

  ui_->cutflow_gas_test_->setStyleSheet(
      gas_test_on ? "background: rgb(0, 255, 0)" : "background: rgb(255, 0, 0)");

  gas_test_on = !gas_test_on;
}

void HPRDiagnose::onManualPumpCtrl() {
  //if (OCutter::GetInstance()->GetController()->dev_comm_->status_ == NULL) {
  //  return;
  //}
  //Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //    status_->plasma_[station_id_].pps_;

  //bool manual_pump_ctrl = status_pps.hyper_.hpr_.manual_pump_ctrl_ == 0;
  //HPRPPSDev::ManualPumpCtrl(station_id_, manual_pump_ctrl ? 1 : 0);
  //ui_->manual_pump_ctrl_->setStyleSheet(
  //    manual_pump_ctrl ? "background: rgb(0, 255, 0)" : "background: rgb(255, 0, 0)");

}

void HPRDiagnose::onSystemReset() {
  //if (OCutter::GetInstance()->GetController()->dev_comm_->status_ == NULL) {
  //  return;
  //}
  //Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //    status_->plasma_[station_id_].pps_;

  //unsigned short pps_state_code = status_pps.hyper_.hpr_.pps_state_code_;
  //unsigned short pps_fault_code = status_pps.hyper_.hpr_.pps_fault_code_;
  //if (pps_fault_code > 79 && pps_state_code == 14) {
  //  HPRPPSDev::Question(station_id_, SYSTEM_RESET);
  //}
}

void HPRDiagnose::onSetParameter() {
  //widget::ConfirmDlg dialog(tr("Set parameter to plasma power supply?"), this);
  //if (dialog.exec() == QDialog::Accepted) {
  //  ui_->hpr_device_config_->Set();
  //  ui_->hpr_device_config_->commit();
  //  emit notify();
  //} else {
  //  ui_->hpr_device_config_->revert();
  //}
}

void HPRDiagnose::onErrorCode() {
  //if (OCutter::GetInstance()->GetController()->dev_comm_->status_ == NULL) {
  //  return;
  //}
  //Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //    status_->plasma_[station_id_].pps_;

  //std::map<std::string, std::string> pps_attr;
  //pps_attr.insert(std::make_pair("model", "HPR"));
  //QString error_code = QObject::tr("Error Code").append(": %1").arg(
  //    status_pps.hyper_.hpr_.pps_fault_code_);

  //QString description = OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "FaultCode", pps_attr,
  //    std::make_pair("code", status_pps.hyper_.hpr_.pps_fault_code_),
  //    "description").c_str();

  //QString implication = OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "FaultCode", pps_attr,
  //    std::make_pair("code", status_pps.hyper_.hpr_.pps_fault_code_),
  //    "implication").c_str();

  //QString resolve = OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "FaultCode", pps_attr,
  //    std::make_pair("code", status_pps.hyper_.hpr_.pps_fault_code_),
  //    "resolve").c_str();

  //ErrorNotifyDlg dialog(this);
  //dialog.setNotify(error_code, description, implication, resolve);
  //dialog.exec();
}

void HPRDiagnose::onClearRecord() {
}

} // namespace cutter
