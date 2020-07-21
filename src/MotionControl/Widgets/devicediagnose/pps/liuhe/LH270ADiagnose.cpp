// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/devicediagnose/pps/liuhe/LH270ADiagnose.h"

#include <QtGui/QButtonGroup>
#include <QtGui/QScrollBar>

#include "cutter/controller/pps/liuhe/LH270APPSDev.h"
#include "cutter/OCutter.h"
#include "cutter/ui_LH270ADiagnose.h"
#include "cutter/widget/deviceconfigwidget/pps/liuhe/LH270APPSDeviceWidget.h"
#include "cutter/widget/specialdialog/DeviceConfigDlg.h"
#include "cutter/widget/specialdialog/ErrorNotifyDlg.h"
#include "device/pps/liuhe/LiuheModbusAddr.h"
#include "nmlclient/NmlClient.h"

namespace cutter {

LH270ADiagnose::LH270ADiagnose(QWidget *parent)
    : QWidget(parent)
    , station_id_(0) {

  ui_ = new Ui::LH270ADiagnose;
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

  initialDiagnoseWidget();
}

LH270ADiagnose::~LH270ADiagnose() {
  delete ui_;
}

void LH270ADiagnose::initialDiagnoseWidget() {
  diagnose_btn_group_ = new QButtonGroup(this);
  diagnose_btn_group_->addButton(ui_->pps_infors_, 0);
  diagnose_btn_group_->addButton(ui_->pps_records_, 1);
  diagnose_btn_group_->addButton(ui_->pps_inputs_, 2);
  diagnose_btn_group_->addButton(ui_->pps_outputs_, 3);
  diagnose_btn_group_->addButton(ui_->gc_inputs_, 4);
  diagnose_btn_group_->addButton(ui_->gc_outputs_, 5);
  connect(diagnose_btn_group_, SIGNAL(buttonClicked(int)), this, SLOT(onSwitchMonitor(int)));

  pps_output_btn_group_ = new QButtonGroup(this);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_1_, 0);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_2_, 1);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_3_, 2);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_4_, 3);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_5_, 4);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_6_, 5);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_7_, 6);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_8_, 7);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_9_, 8);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_10_, 9);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_11_, 10);
  connect(pps_output_btn_group_, SIGNAL(buttonClicked(int)), this, SLOT(onPPSOutputSwitch(int)));

  gc_output_btn_group_ = new QButtonGroup(this);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_1_, 0);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_2_, 1);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_3_, 2);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_4_, 3);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_5_, 4);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_6_, 5);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_7_, 6);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_8_, 7);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_9_, 8);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_10_, 9);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_11_, 10);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_12_, 11);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_13_, 12);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_14_, 13);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_15_, 14);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_16_, 15);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_17_, 16);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_18_, 17);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_19_, 18);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_20_, 19);
  connect(gc_output_btn_group_, SIGNAL(buttonClicked(int)), this, SLOT(onGCOutputSwitch(int)));

  connect(ui_->connect_btn_, SIGNAL(clicked()), this, SLOT(onConnect()));
  connect(ui_->debug_mode_btn_, SIGNAL(clicked()), this, SLOT(onDebugMode()));
  connect(ui_->remote_mode_btn_, SIGNAL(clicked()), this, SLOT(onRemoteMode()));
  connect(ui_->manual_pump_mode_btn_, SIGNAL(clicked()), this, SLOT(onManualPumpMode()));
  connect(ui_->manual_pump_on_btn_, SIGNAL(clicked()), this, SLOT(onManualPumpOn()));
  connect(ui_->manual_pump_off_btn_, SIGNAL(clicked()), this, SLOT(onManualPumpOff()));
  connect(ui_->preflow_gas_set_btn_, SIGNAL(clicked()), this, SLOT(onPreflowGasSet()));
  connect(ui_->cutflow_gas_set_btn_, SIGNAL(clicked()), this, SLOT(onCutflowGasSet()));
  connect(ui_->gas_leak_test_mode_btn_, SIGNAL(clicked()), this, SLOT(onGasLeakTestMode()));
  connect(ui_->inlet_leak_test_btn_, SIGNAL(clicked()), this, SLOT(onInletLeakTest()));
  connect(ui_->system_leak_test_btn_, SIGNAL(clicked()), this, SLOT(onSystemLeakTest()));
  connect(ui_->proportion_valves_check_btn_, SIGNAL(clicked()), this, SLOT(onProportionValvesCheck()));
  connect(ui_->fault_code_resolve_btn_, SIGNAL(clicked()), this, SLOT(onResolve()));
  connect(ui_->set_btn_, SIGNAL(clicked()), this, SLOT(onSetting()));

  ui_->error_log_->setMinimumSize(400, 300);
  ui_->error_log_->setSelectionMode(QAbstractItemView::SingleSelection);
  ui_->error_log_->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{width:30px}");
  ui_->error_log_->setModel(OCutter::GetInstance()->GetPPSErrorLogModel());
  ui_->error_log_->verticalHeader()->setResizeMode(QHeaderView::Fixed);
  ui_->error_log_->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
  ui_->error_log_->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
  ui_->error_log_->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
}

void LH270ADiagnose::setCurrentStation(int station_id) {
  station_id_ = station_id;
}

void LH270ADiagnose::Update() {
  if (OCutter::GetInstance()->GetController()->dev_comm_->status_ == NULL) {
    return;
  }
  if (ui_->stack_->currentWidget() == ui_->pps_inputs_page_) {
    UpdatePPSInputs();
  } else if (ui_->stack_->currentWidget() == ui_->pps_outputs_page_) {
    UpdatePPSOutputs();
  } else if (ui_->stack_->currentWidget() == ui_->gc_inputs_page_) {
    UpdateGCInputs();
  } else if (ui_->stack_->currentWidget() == ui_->gc_outputs_page_) {
    UpdateGCOutputs();
  } else if (ui_->stack_->currentWidget() == ui_->pps_infors_page_) {
    UpdatePPSInfors();
  } else if (ui_->stack_->currentWidget() == ui_->pps_records_page_) {
    UpdatePPSRecords();
  }
}

void LH270ADiagnose::UpdatePPSInfors() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  unsigned short chopper_A_PWM_duty = status_pps.liuhe_.chopper_A_PWM_duty_;
  unsigned short chopper_B_PWM_duty = status_pps.liuhe_.chopper_B_PWM_duty_;
  unsigned short cur_A_current = status_pps.liuhe_.cur_A_current_;
  unsigned short cur_B_current = status_pps.liuhe_.cur_B_current_;
  unsigned short cur_work_current = status_pps.liuhe_.cur_work_current_;
  unsigned short transformer_temperature = status_pps.liuhe_.transformer_temperature_;
  unsigned short chopper_A_temperature = status_pps.liuhe_.chopper_A_temperature_;
  unsigned short chopper_B_temperature = status_pps.liuhe_.chopper_B_temperature_;
  unsigned short coolant_temperature = status_pps.liuhe_.coolant_temperature_;
  unsigned short line_voltage = status_pps.liuhe_.line_voltage_;
  unsigned short coolant_flow = status_pps.liuhe_.coolant_flow_;
  unsigned short cur_pps_current_setpoint = status_pps.liuhe_.cur_pps_current_setpoint_;
  unsigned short cur_pps_state_code = status_pps.liuhe_.cur_pps_state_code_;
  unsigned short cur_pps_fault_code = status_pps.liuhe_.cur_pps_fault_code_;
  unsigned short preflow_plasma_gas_pressure = status_pps.liuhe_.preflow_plasma_gas_pressure_;
  unsigned short preflow_shield_gas_pressure = status_pps.liuhe_.preflow_shield_gas_pressure_;
  unsigned short cutflow_plasma_gas_pressure = status_pps.liuhe_.cutflow_plasma_gas_pressure_;
  unsigned short cutflow_shield_gas_pressure = status_pps.liuhe_.cutflow_shield_gas_pressure_;
  unsigned short cut_gas_1_pressure = status_pps.liuhe_.cut_gas_1_pressure_;
  unsigned short cut_gas_2_pressure = status_pps.liuhe_.cut_gas_2_pressure_;
  unsigned short plasma_gas_type = status_pps.liuhe_.plasma_gas_type_;
  unsigned short shield_gas_type = status_pps.liuhe_.shield_gas_type_;

  unsigned short remote_mode = status_pps.liuhe_.remote_mode_;
  unsigned short manual_pump_mode = status_pps.liuhe_.manual_pump_mode_;
  unsigned short pps_model = status_pps.liuhe_.pps_model_;
  unsigned short gc_model = status_pps.liuhe_.gc_model_;
  unsigned short pps_software_version = status_pps.liuhe_.pps_software_version_;
  unsigned short gc_software_version = status_pps.liuhe_.gc_software_version_;

  ui_->chopper_A_PWM_duty_->setText(QString::number(chopper_A_PWM_duty));
  ui_->chopper_B_PWM_duty_->setText(QString::number(chopper_B_PWM_duty));
  ui_->cur_A_current_->setText(QString::number(cur_A_current));
  ui_->cur_B_current_->setText(QString::number(cur_B_current));
  ui_->cur_work_current_->setText(QString::number(cur_work_current));
  ui_->line_voltage_->setText(QString::number(line_voltage));
  ui_->coolant_flow_->setText(QString::number(coolant_flow / 100., 'f', 2));
  ui_->current_setpoint_->setText(QString::number(cur_pps_current_setpoint));
  ui_->cur_state_code_->setText(QString::number(cur_pps_state_code));
  ui_->cur_fault_code_->setText(QString::number(cur_pps_fault_code));
  ui_->preflow_plasma_gas_pressure_->setText(QString::number(preflow_plasma_gas_pressure));
  ui_->preflow_shield_gas_pressure_->setText(QString::number(preflow_shield_gas_pressure));
  ui_->cutflow_plasma_gas_pressure_->setText(QString::number(cutflow_plasma_gas_pressure));
  ui_->cutflow_shield_gas_pressure_->setText(QString::number(cutflow_shield_gas_pressure));
  ui_->cut_gas1_gas_pressure_->setText(QString::number(cut_gas_1_pressure));
  ui_->cut_gas2_gas_pressure_->setText(QString::number(cut_gas_2_pressure));
  ui_->plasma_gas_type_->setText(OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
      "GasType", std::make_pair("code", plasma_gas_type), "type").c_str());
  ui_->shield_gas_type_->setText(OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
      "GasType", std::make_pair("code", shield_gas_type), "type").c_str());
  std::map<std::string, std::string> temperature_infor;
  temperature_infor.insert(std::make_pair("model", "NTC3950_10K"));
  ui_->transformer_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "Temperature", temperature_infor, std::make_pair("code", transformer_temperature),
      "value").c_str());
  ui_->chopper_A_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "Temperature", temperature_infor, std::make_pair("code", chopper_A_temperature),
      "value").c_str());
  ui_->chopper_B_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "Temperature", temperature_infor, std::make_pair("code", chopper_B_temperature),
      "value").c_str());
  ui_->coolant_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "Temperature", temperature_infor, std::make_pair("code", coolant_temperature),
      "value").c_str());

  ui_->pps_model_->setText(
      OCutter::GetInstance()->GetPPSInfor()->GetItemValue("PPSModel",
      std::make_pair("code", pps_model), "model").c_str());

  ui_->gc_model_->setText(
      OCutter::GetInstance()->GetPPSInfor()->GetItemValue("PGCModel",
      std::make_pair("code", gc_model), "model").c_str());

  ui_->pps_software_version_->setText(QString::number(pps_software_version));
  ui_->gc_software_version_->setText(QString::number(gc_software_version));

  ui_->state_code_description_->setText(OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
      "StateCode", std::make_pair("code", status_pps.liuhe_.cur_pps_state_code_),
      "description").c_str());

  ui_->state_code_implication_->setText(OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
      "StateCode", std::make_pair("code", status_pps.liuhe_.cur_pps_state_code_),
      "implication").c_str());

  ui_->fault_code_description_->setText(OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
      "FaultCode", std::make_pair("code", status_pps.liuhe_.cur_pps_fault_code_),
      "description").c_str());

  ui_->fault_code_implication_->setText(OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
      "FaultCode", std::make_pair("code", status_pps.liuhe_.cur_pps_fault_code_),
      "implication").c_str());

  ui_->connect_state_->setText(QObject::tr("Connecting"));
  ui_->pps_debug_mode_->setText(cur_pps_state_code == 17 ?
      QObject::tr("Debug Mode") : QObject::tr("Exit debug mode"));
  ui_->pps_remote_mode_->setText(remote_mode == 0xFFFF ?
      QObject::tr("Remote Mode On") : QObject::tr("Remote Mode Off"));
  if (cur_pps_state_code == 22) {
    ui_->manual_pump_mode_->setText(manual_pump_mode == 0xFFFF ?
        QObject::tr("Manual Pump Mode On") : QObject::tr("Manual Pump Mode Off"));
  } else {
    ui_->manual_pump_mode_->setText(QObject::tr("Exit Manual Pump Mode"));
  }
  if (cur_pps_state_code == 21 || (cur_pps_state_code >= 23 && cur_pps_state_code <= 25)) {
    ui_->gas_leak_test_mode_->setText(QObject::tr("Gas Testing"));
  } else {
    ui_->gas_leak_test_mode_->setText(QObject::tr("Exit Gas Testing"));
  }
}

void LH270ADiagnose::UpdatePPSRecords() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  ui_->arc_on_time_->setText(QString::number(
      LH270APPSDev::Time(status_pps.liuhe_.arc_on_time_)));
  ui_->power_on_time_->setText(QString::number(
      LH270APPSDev::Time(status_pps.liuhe_.power_on_time_)));
  ui_->arc_success_cnt_->setText(QString::number(
      LH270APPSDev::Count(status_pps.liuhe_.arc_success_cnt_)));
  ui_->arc_failure_cnt_->setText(QString::number(
      LH270APPSDev::Count(status_pps.liuhe_.arc_failure_cnt_)));
  ui_->rampdown_error_cnt_->setText(QString::number(
      LH270APPSDev::Count(status_pps.liuhe_.rampdown_error_cnt_)));

  QVector<int> error_logs = QVector<int>::fromStdVector(
      std::vector<int>(status_pps.liuhe_.pps_error_codes_,
                       status_pps.liuhe_.pps_error_codes_ +
                       sizeof(status_pps.liuhe_.pps_error_codes_) /
                       sizeof(unsigned short)));

  OCutter::GetInstance()->GetPPSErrorLogModel()->updateErrorLog(error_logs);
}

void LH270ADiagnose::UpdatePPSInputs() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  ui_->pps_input_1_->setPixmap(status_pps.liuhe_.pps_input_[0] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_input_2_->setPixmap(status_pps.liuhe_.pps_input_[1] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_input_3_->setPixmap(status_pps.liuhe_.pps_input_[2] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_input_4_->setPixmap(status_pps.liuhe_.pps_input_[3] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_input_5_->setPixmap(status_pps.liuhe_.pps_input_[4] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_input_6_->setPixmap(status_pps.liuhe_.pps_input_[5] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_input_7_->setPixmap(status_pps.liuhe_.pps_input_[6] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

}

void LH270ADiagnose::UpdatePPSOutputs() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  ui_->pps_output_switch_1_->setIcon(status_pps.liuhe_.pps_output_[0] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_2_->setIcon(status_pps.liuhe_.pps_output_[1] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_3_->setIcon(status_pps.liuhe_.pps_output_[2] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_4_->setIcon(status_pps.liuhe_.pps_output_[3] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_5_->setIcon(status_pps.liuhe_.pps_output_[4] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_6_->setIcon(status_pps.liuhe_.pps_output_[5] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_7_->setIcon(status_pps.liuhe_.pps_output_[6] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_8_->setIcon(status_pps.liuhe_.pps_output_[7] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_9_->setIcon(status_pps.liuhe_.pps_output_[8] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_10_->setIcon(status_pps.liuhe_.pps_output_[9] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->pps_output_switch_11_->setIcon(status_pps.liuhe_.pps_output_[10] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

}

void LH270ADiagnose::UpdateGCInputs() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  ui_->gc_input_1_->setPixmap(status_pps.liuhe_.gc_input_[0] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_2_->setPixmap(status_pps.liuhe_.gc_input_[1] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_3_->setPixmap(status_pps.liuhe_.gc_input_[2] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_4_->setPixmap(status_pps.liuhe_.gc_input_[3] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_5_->setPixmap(status_pps.liuhe_.gc_input_[4] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_6_->setPixmap(status_pps.liuhe_.gc_input_[5] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_7_->setPixmap(status_pps.liuhe_.gc_input_[6] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_8_->setPixmap(status_pps.liuhe_.gc_input_[7] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_9_->setPixmap(status_pps.liuhe_.gc_input_[8] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_10_->setPixmap(status_pps.liuhe_.gc_input_[9] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_11_->setPixmap(status_pps.liuhe_.gc_input_[10] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_12_->setPixmap(status_pps.liuhe_.gc_input_[11] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_input_13_->setPixmap(status_pps.liuhe_.gc_input_[12] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

}

void LH270ADiagnose::UpdateGCOutputs() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  ui_->gc_output_switch_1_->setIcon(status_pps.liuhe_.gc_output_[0] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_2_->setIcon(status_pps.liuhe_.gc_output_[1] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_3_->setIcon(status_pps.liuhe_.gc_output_[2] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_4_->setIcon(status_pps.liuhe_.gc_output_[3] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_5_->setIcon(status_pps.liuhe_.gc_output_[4] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_6_->setIcon(status_pps.liuhe_.gc_output_[5] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_7_->setIcon(status_pps.liuhe_.gc_output_[6] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_8_->setIcon(status_pps.liuhe_.gc_output_[7] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_9_->setIcon(status_pps.liuhe_.gc_output_[8] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_10_->setIcon(status_pps.liuhe_.gc_output_[9] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_11_->setIcon(status_pps.liuhe_.gc_output_[10] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_12_->setIcon(status_pps.liuhe_.gc_output_[11] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_13_->setIcon(status_pps.liuhe_.gc_output_[12] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_14_->setIcon(status_pps.liuhe_.gc_output_[13] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_15_->setIcon(status_pps.liuhe_.gc_output_[14] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_16_->setIcon(status_pps.liuhe_.gc_output_[15] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_17_->setIcon(status_pps.liuhe_.gc_output_[16] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_18_->setIcon(status_pps.liuhe_.gc_output_[17] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_19_->setIcon(status_pps.liuhe_.gc_output_[18] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  ui_->gc_output_switch_20_->setIcon(status_pps.liuhe_.gc_output_[19] == 1 ?
      QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

}

void LH270ADiagnose::onSwitchMonitor(int monitor_id) {
  switch (monitor_id) {
   case 0:
    ui_->stack_->setCurrentWidget(ui_->pps_infors_page_);
    break;
   case 1:
    ui_->stack_->setCurrentWidget(ui_->pps_records_page_);
    break;
   case 2:
    ui_->stack_->setCurrentWidget(ui_->pps_inputs_page_);
    break;
   case 3:
    ui_->stack_->setCurrentWidget(ui_->pps_outputs_page_);
    break;
   case 4:
    ui_->stack_->setCurrentWidget(ui_->gc_inputs_page_);
    break;
   case 5:
    ui_->stack_->setCurrentWidget(ui_->gc_outputs_page_);
    break;
   default:
    break;
  }
}

void LH270ADiagnose::onPPSOutputSwitch(int index) {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  bool checked = status_pps.liuhe_.pps_output_[index] == 1;
  PPSClient::SendCommandToPPS(station_id_, LIUHE_PPS_OUTPUT_ADDR + index, !checked);
}

void LH270ADiagnose::onGCOutputSwitch(int index) {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  bool checked = status_pps.liuhe_.gc_output_[index] == 1;
  PPSClient::SendCommandToPPS(station_id_, LIUHE_GC_OUTPUT_ADDR + index, !checked);
}

void LH270ADiagnose::onSetting() {
  LH270APPSDeviceWidget *config_widget = new LH270APPSDeviceWidget();
  config_widget->setCurrentStation(station_id_);

  DeviceConfigDlg dialog(this);
  dialog.setConfigWidget(config_widget);
  if (dialog.exec() ==  QDialog::Accepted) {
    config_widget->Set();
    config_widget->commit();
    emit notify();
  } else {
    config_widget->revert();
  }
}

void LH270ADiagnose::onResolve() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  QString error_code = QObject::tr("Error Code").append(": %1").arg(
      status_pps.liuhe_.cur_pps_fault_code_);

  QString description = OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
      "FaultCode",
      std::make_pair("code", status_pps.liuhe_.cur_pps_fault_code_),
      "description").c_str();

  QString implication = OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
      "FaultCode",
      std::make_pair("code", status_pps.liuhe_.cur_pps_fault_code_),
      "implication").c_str();

  QString resolve = OCutter::GetInstance()->GetPPSInfor()->GetItemValue(
      "FaultCode",
      std::make_pair("code", status_pps.liuhe_.cur_pps_fault_code_),
      "resolve").c_str();

  ErrorNotifyDlg dialog(this);
  dialog.setNotify(error_code, description, implication, resolve);
  dialog.exec();
}

void LH270ADiagnose::onConnect() {
}

void LH270ADiagnose::onDebugMode() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  unsigned short status_code = status_pps.liuhe_.cur_pps_state_code_;
  if (status_code == 17) {
    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 1);
  } else if (status_code == 3) {
    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 17);
  }
}

void LH270ADiagnose::onRemoteMode() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  bool remote_mode = status_pps.liuhe_.remote_mode_ == 0xFFFF;
  PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_REMOTE_MODE,
                            remote_mode ? 0x0000 : 0xFFFF);

}

void LH270ADiagnose::onManualPumpMode() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  unsigned short status_code = status_pps.liuhe_.cur_pps_state_code_;
  if (status_code == 22) {
    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 3);
  } else if (status_code == 3) {
    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 22);
  }
}

void LH270ADiagnose::onManualPumpOn() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  if (status_pps.liuhe_.cur_pps_state_code_ == 22) {
    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_MANUAL_PUMP_MODE, 0xFFFF);
  }
}

void LH270ADiagnose::onManualPumpOff() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  if (status_pps.liuhe_.cur_pps_state_code_ == 22) {
    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_MANUAL_PUMP_MODE, 0x0000);
  }
}

void LH270ADiagnose::onPreflowGasSet() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  if (status_pps.liuhe_.cur_pps_state_code_ == 3 ||
      status_pps.liuhe_.cur_pps_state_code_ == 12) {

    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 20);
  } else if (status_pps.liuhe_.cur_pps_state_code_ == 20) {
    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 3);
  }
}

void LH270ADiagnose::onCutflowGasSet() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  if (status_pps.liuhe_.cur_pps_state_code_ == 3 ||
      status_pps.liuhe_.cur_pps_state_code_ == 20) {

    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 12);
  } else if (status_pps.liuhe_.cur_pps_state_code_ == 12) {
    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 3);
  }
}

void LH270ADiagnose::onGasLeakTestMode() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  if (status_pps.liuhe_.cur_pps_state_code_ == 1 ||
      status_pps.liuhe_.cur_pps_state_code_ == 3 ||
      status_pps.liuhe_.cur_pps_state_code_ == 23 ||
      status_pps.liuhe_.cur_pps_state_code_ == 24 ||
      status_pps.liuhe_.cur_pps_state_code_ == 25) {

    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 21);
  } else if (status_pps.liuhe_.cur_pps_state_code_ == 21) {
    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 2);
  }
}

void LH270ADiagnose::onInletLeakTest() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  if (status_pps.liuhe_.cur_pps_state_code_ == 21 ||
      status_pps.liuhe_.cur_pps_state_code_ == 24 ||
      status_pps.liuhe_.cur_pps_state_code_ == 25) {

    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 23);
  }
}

void LH270ADiagnose::onSystemLeakTest() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  if (status_pps.liuhe_.cur_pps_state_code_ == 21 ||
      status_pps.liuhe_.cur_pps_state_code_ == 23 ||
      status_pps.liuhe_.cur_pps_state_code_ == 25) {

    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 24);
  }
}

void LH270ADiagnose::onProportionValvesCheck() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  if (status_pps.liuhe_.cur_pps_state_code_ == 21 ||
      status_pps.liuhe_.cur_pps_state_code_ == 23 ||
      status_pps.liuhe_.cur_pps_state_code_ == 24) {

    PPSClient::SendParamToPPS(station_id_, LIUHE_PPS_STATE_CODE_SET, 25);
  }
}

} // namespace cutter
