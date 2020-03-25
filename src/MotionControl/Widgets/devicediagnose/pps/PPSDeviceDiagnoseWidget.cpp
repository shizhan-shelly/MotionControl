// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Widgets/devicediagnose/pps/PPSDeviceDiagnoseWidget.h"

//#include "cutter/baseclass/parameter/ParamModeler.h"
#include "MotionControl/Widgets/devicediagnose/pps/liuhe/LH270ADiagnose.h"
#include "MotionControl/Widgets/devicediagnose/pps/hyper/HPRDiagnose.h"
#include "MotionControl/Widgets/devicediagnose/pps/hyper/PowermaxDiagnose.h"
#include "ui_PPSDeviceDiagnoseWidget.h"

namespace cutter {

PPSDeviceDiagnoseWidget::PPSDeviceDiagnoseWidget(QWidget *parent)
    : QWidget(parent)
    , station_id_(0) {

  ui_ = new Ui::PPSDeviceDiagnoseWidget;
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt; font-family: SimSun } \
                 QTabWidget::pane {border: none; \
                                   background: transparent;} \
                 QTabBar::tab {min-width: 70px; \
                               min-height: 40px;} \
                 QTabBar::tab:selected {color: rgb(85, 170, 255);} \
                 QTabBar::tab:!selected {color: black;}");

  initialDiagnoseWidget();
}

PPSDeviceDiagnoseWidget::~PPSDeviceDiagnoseWidget() {
  delete ui_;
}

void PPSDeviceDiagnoseWidget::Update() {
  //ParamModeler *modeler = ParamModeler::GetInstance();
  //parameter::F7000PPSElement *pps = modeler->f7000_->plcconfig_->
  //    GetStationPtr(station_id_)->stationplasma_->pps_;

  //std::string pps_vendor = pps->ppsvendor_->GetValue();
  //if (pps_vendor.compare("Hypertherm") == 0) {
  //  std::string pps_model = pps->ppshyper_->ppshypertype_->GetValue();
  //  if (pps_model.compare("Powermax") == 0) {
  //    powermax_->Update();
  //  } else if (pps_model.compare("HPR") == 0) {
  //    hpr_->Update();
  //  }
  //} else if (pps_vendor.compare("Liuhe") == 0) {
  //  lh_->Update();
  //}
}

void PPSDeviceDiagnoseWidget::onStationIndex(int index) {
  station_id_ = index;
  if (station_id_ == 0) {
    powermax_->setCurrentStation(station_id_);
  } else {
    lh_->setCurrentStation(station_id_);
  }
  //ParamModeler *modeler = ParamModeler::GetInstance();
  //parameter::F7000PPSElement *pps = modeler->f7000_->plcconfig_->
  //    GetStationPtr(station_id_)->stationplasma_->pps_;

  //std::string pps_vendor = pps->ppsvendor_->GetValue();
  //if (pps_vendor.compare("Hypertherm") == 0) {
  //  std::string pps_model = pps->ppshyper_->ppshypertype_->GetValue();
  //  if (pps_model.compare("Powermax") == 0) {
  //    powermax_->setCurrentStation(station_id_);
  //  } else if (pps_model.compare("HPR") == 0) {
  //    hpr_->setCurrentStation(station_id_);
  //  }
  //} else if (pps_vendor.compare("Liuhe") == 0) {
  //  lh_->setCurrentStation(station_id_);
  //}
}

void PPSDeviceDiagnoseWidget::initialDiagnoseWidget() {
  connect(ui_->pps_tab_, SIGNAL(currentChanged(int)),
      this, SLOT(onStationIndex(int)));

  powermax_ = new PowermaxDiagnose();
  hpr_ = new HPRDiagnose();
  lh_ = new LH270ADiagnose();
  //ParamModeler *modeler = ParamModeler::GetInstance();
  //int station_size = modeler->f7000_->plcconfig_->Station_size();
  //for (int i = 0; i < station_size; i++) {
  //  parameter::F7000PPSElement *pps = modeler->f7000_->plcconfig_->
  //      GetStationPtr(i)->stationplasma_->pps_;

  //  std::string pps_vendor = pps->ppsvendor_->GetValue();
  //  if (pps_vendor.compare("Hypertherm") == 0) {
  //    std::string pps_model = pps->ppshyper_->ppshypertype_->GetValue();
  //    if (pps_model.compare("Powermax") == 0) {
  //      ui_->pps_tab_->insertTab(i, powermax_, QObject::tr("Hypertherm"));
  //    } else if (pps_model.compare("HPR") == 0) {
  //      ui_->pps_tab_->insertTab(i, hpr_, QObject::tr("Hypertherm"));
  //    } else {
  //      QWidget *undefine_ = new QWidget();
  //      ui_->pps_tab_->insertTab(i, undefine_, QObject::tr("Undefine"));
  //    }
  //  } else if (pps_vendor.compare("Liuhe") == 0) {
  //    ui_->pps_tab_->insertTab(i, lh_, QObject::tr("Liuhe"));
  //  } else {
  //    QWidget *undefine_ = new QWidget();
  //    ui_->pps_tab_->insertTab(i, undefine_, QObject::tr("Undefine"));
  //  }
  //}
  ui_->pps_tab_->insertTab(0, powermax_, QObject::tr("Hypertherm"));
  ui_->pps_tab_->insertTab(1, lh_, QObject::tr("Liuhe"));
  ui_->pps_tab_->setCurrentIndex(0);
}

} // namespace cutter
