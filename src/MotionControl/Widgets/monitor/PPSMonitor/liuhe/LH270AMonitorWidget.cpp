// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/IOMonitorWidget/PPSMonitor/liuhe/LH270AMonitorWidget.h"

#include "cutter/controller/pps/liuhe/LH270APPSDev.h"
#include "cutter/OCutter.h"
#include "cutter/ui_LH270AMonitorWidget.h"
#include "nmlclient/NmlClient.h"

namespace cutter {

LH270AMonitorWidget::LH270AMonitorWidget(QWidget *parent)
    : QWidget(parent)
    , station_id_(0) {

  ui_ = new Ui::LH270AMonitorWidget();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

  connect(ui_->state_code_btn_, SIGNAL(clicked()), this, SLOT(onStateCode()));
  connect(ui_->fault_code_btn_, SIGNAL(clicked()), this, SLOT(onFaultCode()));
  ui_->text_widget_->hide();
}

LH270AMonitorWidget::~LH270AMonitorWidget() {
  delete ui_;
}

void LH270AMonitorWidget::setCurrentStation(int station_id) {
  station_id_ = station_id;
}

void LH270AMonitorWidget::Update() {
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->station_manager_.stations_[station_id_].plasma_.pps_;

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

  ui_->cur_A_current_->setText(QString::number(cur_A_current));
  ui_->cur_B_current_->setText(QString::number(cur_B_current));
  ui_->cur_work_current_->setText(QString::number(cur_work_current));
  ui_->line_voltage_->setText(QString::number(line_voltage));
  ui_->coolant_flow_->setText(QString::number(coolant_flow));
  ui_->current_setpoint_->setText(QString::number(cur_pps_current_setpoint));
  ui_->cur_state_code_->setText(QString::number(cur_pps_state_code));
  ui_->cur_fault_code_->setText(QString::number(cur_pps_fault_code));
  ui_->plasma_gas_type_->setText(LH270APPSDev::GasType(plasma_gas_type).c_str());
  ui_->shield_gas_type_->setText(LH270APPSDev::GasType(shield_gas_type).c_str());
  ui_->preflow_plasma_gas_pressure_->setText(QString::number(preflow_plasma_gas_pressure));
  ui_->preflow_shield_gas_pressure_->setText(QString::number(preflow_shield_gas_pressure));
  ui_->cutflow_plasma_gas_pressure_->setText(QString::number(cutflow_plasma_gas_pressure));
  ui_->cutflow_shield_gas_pressure_->setText(QString::number(cutflow_shield_gas_pressure));
  ui_->cut_gas_1_pressure_->setText(QString::number(cut_gas_1_pressure));
  ui_->cut_gas_2_pressure_->setText(QString::number(cut_gas_2_pressure));
  ui_->transformer_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "Temperature", LH270APPSDev::Temperature(transformer_temperature), "value").c_str());
  ui_->chopper_A_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "Temperature", LH270APPSDev::Temperature(chopper_A_temperature), "value").c_str());
  ui_->chopper_B_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "Temperature", LH270APPSDev::Temperature(chopper_B_temperature), "value").c_str());
  ui_->coolant_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
      "Temperature", LH270APPSDev::Temperature(coolant_temperature), "value").c_str());

}

void LH270AMonitorWidget::onStateCode() {
  if (ui_->state_code_btn_->arrowType() == Qt::UpArrow) {
    ui_->state_code_btn_->setArrowType(Qt::DownArrow);
    ui_->text_widget_->hide();
  } else {
    Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
        status_->station_manager_.stations_[station_id_].plasma_.pps_;

    QString description = OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
        "StateCode",
        LH270APPSDev::StateCode(status_pps.liuhe_.cur_pps_state_code_),
        "description").c_str();

    QString implication = OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
        "StateCode",
        LH270APPSDev::StateCode(status_pps.liuhe_.cur_pps_state_code_),
        "implication").c_str();

    ui_->state_code_btn_->setArrowType(Qt::UpArrow);
    ui_->state_code_widget_->setTextTitle(description);
    ui_->state_code_widget_->setTextContent(implication);
    ui_->text_widget_->setCurrentWidget(ui_->state_code_widget_);
    ui_->text_widget_->show();
  }
}

void LH270AMonitorWidget::onFaultCode() {
  if (ui_->fault_code_btn_->arrowType() == Qt::UpArrow) {
    ui_->fault_code_btn_->setArrowType(Qt::DownArrow);
    ui_->text_widget_->hide();
  } else {
    Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
        status_->station_manager_.stations_[station_id_].plasma_.pps_;

    QString description = OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
        "FaultCode",
        LH270APPSDev::FaultCode(status_pps.liuhe_.cur_pps_fault_code_),
        "description").c_str();

    QString resolve = OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
        "FaultCode",
        LH270APPSDev::FaultCode(status_pps.liuhe_.cur_pps_fault_code_),
        "resolve").c_str();

    ui_->fault_code_btn_->setArrowType(Qt::UpArrow);
    ui_->fault_code_widget_->setTextTitle(description);
    ui_->fault_code_widget_->setTextContent(resolve);
    ui_->text_widget_->setCurrentWidget(ui_->fault_code_widget_);
    ui_->text_widget_->show();
  }
}

} // namespace cutter
