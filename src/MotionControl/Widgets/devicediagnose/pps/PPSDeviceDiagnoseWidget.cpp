// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/devicediagnose/pps/PPSDeviceDiagnoseWidget.h"

#include "cutter/baseclass/parameter/ParamModeler.h"
#include "cutter/controller/pps/PPSClient.h"
#include "cutter/OCutter.h"
#include "cutter/ui_PPSDeviceDiagnoseWidget.h"

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
  ParamModeler *modeler = ParamModeler::GetInstance();
  parameter::F7000PPSElement *pps = modeler->f7000_->plcconfig_->
      GetStationPtr(station_id_)->stationplasma_->pps_;

  std::string pps_vendor = pps->ppsvendor_->GetValue();
  if (pps_vendor.compare("Hypertherm") == 0) {
    std::string pps_model = pps->ppshyper_->ppshypertype_->GetValue();
    if (pps_model.compare("Powermax") == 0) {
      ui_->powermax_->Update();
    } else if (pps_model.compare("HPR") == 0) {
      ui_->hpr_->Update();
    }
  } else if (pps_vendor.compare("Liuhe") == 0) {
    ui_->lh270a_->Update();
  } else if (pps_vendor.compare("Kjellberg") == 0) {
    ui_->kjellberg_->Update();
  }
}

void PPSDeviceDiagnoseWidget::onStationIndex(int index) {
  station_id_ = index;
  ParamModeler *modeler = ParamModeler::GetInstance();
  parameter::F7000PPSElement *pps = modeler->f7000_->plcconfig_->
      GetStationPtr(station_id_)->stationplasma_->pps_;

  std::string pps_vendor = pps->ppsvendor_->GetValue();
  if (pps_vendor.compare("Hypertherm") == 0) {
    std::string pps_model = pps->ppshyper_->ppshypertype_->GetValue();
    if (pps_model.compare("Powermax") == 0) {
      ui_->stack_->setCurrentWidget(ui_->powermax_);
      ui_->powermax_->setCurrentStation(station_id_);
    } else if (pps_model.compare("HPR") == 0) {
      ui_->stack_->setCurrentWidget(ui_->hpr_);
      ui_->hpr_->setCurrentStation(station_id_);
    } else {
      ui_->stack_->setCurrentWidget(ui_->none_);
    }
  } else if (pps_vendor.compare("Liuhe") == 0) {
    ui_->stack_->setCurrentWidget(ui_->lh270a_);
    ui_->lh270a_->setCurrentStation(station_id_);
  } else if (pps_vendor.compare("Kjellberg") == 0) {
    ui_->stack_->setCurrentWidget(ui_->kjellberg_);
    ui_->kjellberg_->setCurrentStation(station_id_);
  } else {
    ui_->stack_->setCurrentWidget(ui_->none_);
  }
}

void PPSDeviceDiagnoseWidget::onNotify() {
  OCutter *cutter = OCutter::GetInstance();
  ParamModeler *modeler = ParamModeler::GetInstance();
  modeler->WriteToXml(cutter->GetXMLConfigPath().toStdString());
  cutter->SendXmlFileToCnc();

  std::map<int, PPSClient *> pps_dev = cutter->pps_factory_.GetPPSDev();
  std::map<int, PPSClient *>::const_iterator it = pps_dev.find(station_id_);
  if (it != pps_dev.end()) {
    if (it->second) {
      it->second->NotifyParams();
    }
  }
}

void PPSDeviceDiagnoseWidget::initialDiagnoseWidget() {
  connect(ui_->tab_bar_, SIGNAL(currentChanged(int)),
      this, SLOT(onStationIndex(int)));

  connect(ui_->hpr_, SIGNAL(notify()), this, SLOT(onNotify()));
  connect(ui_->lh270a_, SIGNAL(notify()), this, SLOT(onNotify()));
  connect(ui_->kjellberg_, SIGNAL(notify()), this, SLOT(onNotify()));

  QMap<int, QString> infor;
  ParamModeler *modeler = ParamModeler::GetInstance();
  int station_size = modeler->f7000_->plcconfig_->Station_size();
  for (int i = 0; i < station_size; i++) {
    parameter::F7000PPSElement *pps = modeler->f7000_->plcconfig_->
        GetStationPtr(i)->stationplasma_->pps_;

    std::string pps_vendor = pps->ppsvendor_->GetValue();
    if (pps_vendor.compare("Hypertherm") == 0) {
      infor.insert(i, pps->ppshyper_->ppshypertype_->GetValue().c_str());
    } else if (pps_vendor.compare("Liuhe") == 0) {
      infor.insert(i, pps->ppsliuhe_->ppsliuhetype_->GetValue().c_str());
    } else if (pps_vendor.compare("Kjellberg") == 0) {
      infor.insert(i, pps->ppskjellberg_->ppskjellbergtype_->GetValue().c_str());
    } else {
      infor.insert(i, QObject::tr("Undefine"));
    }
  }
  ui_->tab_bar_->initBar(infor);
  ui_->tab_bar_->setCurrentIndex(0);
}

void PPSDeviceDiagnoseWidget::showEvent(QShowEvent *event) {
  int id = ui_->tab_bar_->currentIndex();
  if (id >= 0) {
    onStationIndex(id);
  }
  QWidget::showEvent(event);
}

} // namespace cutter
