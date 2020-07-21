// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/devicediagnose/pps/kjellberg/KjellbergDiagnose.h"

#include "cutter/controller/pps/kjellberg/KjellbergPPSDev.h"
#include "cutter/OCutter.h"
#include "cutter/ui_KjellbergDiagnose.h"
#include "cutter/widget/deviceconfigwidget/pps/kjellberg/KjellbergPGCDeviceWidget.h"
#include "cutter/widget/deviceconfigwidget/pps/kjellberg/KjellbergPPSDeviceWidget.h"
#include "cutter/widget/devicediagnose/pps/kjellberg/DigitalInputWidget.h"
#include "cutter/widget/devicediagnose/pps/kjellberg/DigitalSignalWidget.h"
#include "cutter/widget/specialdialog/DeviceConfigDlg.h"
#include "cutter/widget/specialdialog/DeviceDiagnoseDlg.h"
#include "nmlclient/NmlClient.h"

namespace cutter {

KjellbergDiagnose::KjellbergDiagnose(QWidget *parent)
    : QWidget(parent)
    , station_id_(0) {

  ui_ = new Ui::KjellbergDiagnose();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

  initialDiagnoseWidget();
}

KjellbergDiagnose::~KjellbergDiagnose() {
  delete ui_;
}

void KjellbergDiagnose::initialDiagnoseWidget() {
  connect(ui_->pps_query_device_info_btn_, SIGNAL(clicked()), this, SLOT(onPPSQueryDeviceInfor()));
  connect(ui_->pps_query_parameter_btn_, SIGNAL(clicked()), this, SLOT(onPPSQueryParameter()));
  connect(ui_->pps_set_parameter_long_btn_, SIGNAL(clicked()), this, SLOT(onPPSTransmitParamLong()));
  connect(ui_->pps_set_parameter_short_btn_, SIGNAL(clicked()), this, SLOT(onPPSTransmitParamShort()));
  connect(ui_->pps_remote_mode_off_btn_, SIGNAL(clicked()), this, SLOT(onPPSRemoteOff()));
  connect(ui_->pgc_query_device_info_btn_, SIGNAL(clicked()), this, SLOT(onPGCQueryDeviceInfor()));
  connect(ui_->pgc_query_parameter_btn_, SIGNAL(clicked()), this, SLOT(onPGCQueryParameter()));
  connect(ui_->pgc_set_parameter_btn_, SIGNAL(clicked()), this, SLOT(onPGCTransmitParameter()));

  connect(ui_->digital_input_btn_, SIGNAL(clicked()), this, SLOT(onDigitalInput()));
  connect(ui_->digital_signals_btn_, SIGNAL(clicked()), this, SLOT(onDigitalSignals()));
  connect(ui_->pps_edit_btn_, SIGNAL(clicked()), this, SLOT(onEditPPSParameter()));
  connect(ui_->pgc_edit_btn_, SIGNAL(clicked()), this, SLOT(onEditPGCParameter()));

  connect(ui_->ps_error_code_btn_, SIGNAL(clicked()), this, SLOT(onPPSErrorCodeShow()));
  connect(ui_->ps_state_code_btn_, SIGNAL(clicked()), this, SLOT(onPPSStatusCodeShow()));
  connect(ui_->ps_warning_code_btn_, SIGNAL(clicked()), this, SLOT(onPPSWarningCodeShow()));
  connect(ui_->pgc_error_code_btn_, SIGNAL(clicked()), this, SLOT(onPGCErrorCodeShow()));
  connect(ui_->pgc_status_code_btn_, SIGNAL(clicked()), this, SLOT(onPGCStatusCodeShow()));
}

void KjellbergDiagnose::onDigitalInput() {
  DigitalInputWidget *digital_input = new DigitalInputWidget();
  digital_input->setCurrentStation(station_id_);
  digital_input->SetClickable(false);
  DeviceDiagnoseDlg dialog(this);
  dialog.setDiagnoseWidget(digital_input);
  dialog.exec();
}

void KjellbergDiagnose::onDigitalSignals() {
  DigitalSignalWidget *digital_signal = new DigitalSignalWidget();
  digital_signal->setCurrentStation(station_id_);
  DeviceDiagnoseDlg dialog(this);
  dialog.setDiagnoseWidget(digital_signal);
  dialog.exec();
}

void KjellbergDiagnose::setCurrentStation(int station_id) {
  station_id_ = station_id;
}

void KjellbergDiagnose::Update() {
  if (OCutter::GetInstance()->GetController()->dev_comm_->status_ == NULL) {
    return;
  }
  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
      status_->plasma_[station_id_].pps_;

  unsigned short ps_device_type = status_pps.kjellberg_.ps_device_type_;
  unsigned short ps_version = status_pps.kjellberg_.ps_version_;
  unsigned short actual_cutting_current = status_pps.kjellberg_.actual_cutting_current_;
  unsigned short actual_cutting_voltage = status_pps.kjellberg_.actual_cutting_voltage_;
  unsigned short cutting_current_set = status_pps.kjellberg_.cutting_current_set_;
  unsigned short corner_current_set = status_pps.kjellberg_.corner_current_set_;
  unsigned char digital_signals = status_pps.kjellberg_.digital_signals_;
  unsigned char time_pre_flow_gas = status_pps.kjellberg_.time_pre_flow_gas_;
  unsigned char time_post_flow_gas = status_pps.kjellberg_.time_post_flow_gas_;
  unsigned char time_up_slope = status_pps.kjellberg_.time_up_slope_;
  unsigned char time_down_slope = status_pps.kjellberg_.time_down_slope_;
  unsigned char status_code_ps = status_pps.kjellberg_.status_code_ps_;
  unsigned short last_error_code_ps = status_pps.kjellberg_.last_error_code_ps_;
  unsigned short time_of_cuts = status_pps.kjellberg_.time_of_cuts_;
  unsigned short number_of_cuts = status_pps.kjellberg_.number_of_cuts_;
  unsigned short number_of_arc_interruptions = status_pps.kjellberg_.number_of_arc_interruptions_;
  unsigned char digital_inputs_1 = status_pps.kjellberg_.digital_inputs_1_;
  unsigned char digital_inputs_2 = status_pps.kjellberg_.digital_inputs_2_;
  unsigned char warning_code_ps = status_pps.kjellberg_.warning_code_ps_;

  ui_->pps_device_type_->setText(
      OCutter::GetInstance()->GetPPSInfor()->GetItemValue("PPSModel",
      std::make_pair("code", ps_device_type), "model").c_str());

  ui_->pps_version_->setText(QString::number(ps_version / 100., 'f', 2));
  ui_->cutting_current_->setText(QString::number(actual_cutting_current));
  ui_->cutting_voltage_->setText(QString::number(actual_cutting_voltage));
  ui_->digital_signals_->setText(QString::number(digital_signals));
  ui_->preflow_gas_->setText(QString::number(time_pre_flow_gas / 10., 'f', 2));
  ui_->postflow_gas_->setText(QString::number(time_post_flow_gas / 10., 'f', 2));
  ui_->up_slope_->setText(QString::number(time_up_slope / 100., 'f', 2));
  ui_->down_slope_->setText(QString::number(time_down_slope / 100, 'f', 2));
  ui_->cutting_current_set_value_->setText(QString::number(cutting_current_set));
  ui_->corner_current_set_value_->setText(QString::number(corner_current_set));
  ui_->ps_state_code_->setText(QString::number(status_code_ps));
  ui_->ps_last_error_code_->setText(QString::number(last_error_code_ps));
  ui_->cut_time_->setText(QString::number(time_of_cuts));
  ui_->cut_number_->setText(QString::number(number_of_cuts));
  ui_->arc_interruptions_->setText(QString::number(number_of_arc_interruptions));
  ui_->digital_input_1_->setText(QString::number(digital_inputs_1));
  ui_->digital_input_2_->setText(QString::number(digital_inputs_2));
  ui_->ps_warning_code_->setText(QString::number(warning_code_ps));

  unsigned short gc_device_type = status_pps.kjellberg_.gc_device_type_;
  unsigned short gas_code_hex = status_pps.kjellberg_.gas_code_hex_;
  unsigned short gas_pressure_PG1 = status_pps.kjellberg_.gas_pressure_PG1_;
  unsigned short gas_pressure_PG2 = status_pps.kjellberg_.gas_pressure_PG2_;
  unsigned short gas_pressure_PG3 = status_pps.kjellberg_.gas_pressure_PG3_;
  unsigned short gas_pressure_WG1 = status_pps.kjellberg_.gas_pressure_WG1_;
  unsigned short gas_pressure_WG2 = status_pps.kjellberg_.gas_pressure_WG2_;
  unsigned short special_code_hex = status_pps.kjellberg_.special_code_hex_;
  unsigned short cutting_pressure_set = status_pps.kjellberg_.cutting_pressure_set_;
  unsigned short status_code_gc = status_pps.kjellberg_.status_code_gc_;
  unsigned short error_code_gc = status_pps.kjellberg_.error_code_gc_;

  ui_->pgc_device_type_->setText(
      OCutter::GetInstance()->GetPPSInfor()->GetItemValue("PGCModel",
      std::make_pair("code", gc_device_type), "model").c_str());

  //ui_->pgc_main_version_->setText(QString::number());
  //ui_->pgc_sub_version_->setText(QString::number());
  ui_->gas_code_->setText(QString::number(gas_code_hex));
  ui_->gas_pressure_PG1_->setText(QString::number(gas_pressure_PG1));
  ui_->gas_pressure_PG2_->setText(QString::number(gas_pressure_PG2));
  ui_->gas_pressure_PG3_->setText(QString::number(gas_pressure_PG3));
  ui_->gas_pressure_WG1_->setText(QString::number(gas_pressure_WG1));
  ui_->gas_pressure_WG2_->setText(QString::number(gas_pressure_WG2));
  ui_->special_code_->setText(QString::number(special_code_hex));
  ui_->cutting_pressure_set_value_->setText(QString::number(cutting_pressure_set / 10., 'f', 1));
  ui_->pgc_status_code_->setText(QString::number(status_code_gc));
  ui_->pgc_error_code_->setText(QString::number(error_code_gc));
}

void KjellbergDiagnose::onPPSQueryDeviceInfor() {
  KjellbergPPSDev::KJ_PPS_Device(station_id_);
}

void KjellbergDiagnose::onPPSQueryParameter() {
  KjellbergPPSDev::KJ_PPS_Question(station_id_);
}

void KjellbergDiagnose::onPPSTransmitParamLong() {
  KjellbergPPSDev::KJ_PPS_CommandLong(station_id_);
}

void KjellbergDiagnose::onPPSTransmitParamShort() {
  KjellbergPPSDev::KJ_PPS_CommandShort(station_id_);
}

void KjellbergDiagnose::onPPSRemoteOff() {
  KjellbergPPSDev::KJ_PPS_CommandRemoteOff(station_id_);
}

void KjellbergDiagnose::onPGCQueryDeviceInfor() {
  KjellbergPPSDev::KJ_PGC_Device(station_id_);
}

void KjellbergDiagnose::onPGCQueryParameter() {
  KjellbergPPSDev::KJ_PGC_Question(station_id_);
}

void KjellbergDiagnose::onPGCTransmitParameter() {
  KjellbergPPSDev::KJ_PGC_Command(station_id_);
}

void KjellbergDiagnose::onEditPGCParameter() {
  KjellbergPGCDeviceWidget *config_widget = new KjellbergPGCDeviceWidget();
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

void KjellbergDiagnose::onEditPPSParameter() {
  KjellbergPPSDeviceWidget *config_widget = new KjellbergPPSDeviceWidget();
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

void KjellbergDiagnose::onPPSErrorCodeShow() {
}

void KjellbergDiagnose::onPPSStatusCodeShow() {
}

void KjellbergDiagnose::onPPSWarningCodeShow() {
}

void KjellbergDiagnose::onPGCErrorCodeShow() {
}

void KjellbergDiagnose::onPGCStatusCodeShow() {
}

} // namespace cutter
