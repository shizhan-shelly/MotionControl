// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "PPSInfor.h"

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>

PPSInfor::PPSInfor() {}

PPSInfor::~PPSInfor() {}

bool PPSInfor::ParsePPSInfor(const std::string &xml_file) {
  pps_infor_file_ = xml_file;
  QFile file(xml_file.c_str());
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }
  QString error_msg = "";
  int line = 0;
  int column = 0;
  if (!doc_.setContent(&file, &error_msg, &line, &column)) {
    // TODO(Zhan Shi): write error log.
    file.close();
    return false;
  }
  ParseFaultCode();
  ParseStateCode();
  file.close();
  return true;
}


void PPSInfor::ParseStateCode() {
  state_code_.clear();
  QDomElement data_element = doc_.documentElement().firstChildElement("StateCode");
  QDomNodeList records = data_element.childNodes();
  for (int i = 0; i < records.size(); i++) {
    QDomNamedNodeMap node_map = records.item(i).attributes();
    std::string code = node_map.namedItem("code").nodeValue().toStdString();
    std::string description = node_map.namedItem("description").nodeValue().toStdString();
    state_code_.insert(std::make_pair<std::string, std::string>(code, description));
  }
}

void PPSInfor::ParseFaultCode() {
  fault_code_.clear();
  fault_resolve_.clear();
  QDomElement data_element = doc_.documentElement().firstChildElement("FaultCode");
  QDomNodeList records = data_element.childNodes();
  for (int i = 0; i < records.size(); i++) {
    QDomNamedNodeMap node_map = records.item(i).attributes();
    std::string code = node_map.namedItem("code").nodeValue().toStdString();
    std::string description = node_map.namedItem("description").nodeValue().toStdString();
    std::string resolve = node_map.namedItem("resolve").nodeValue().toStdString();
    fault_code_.insert(std::make_pair<std::string, std::string>(code, description));
    fault_resolve_.insert(std::make_pair<std::string, std::string>(code, resolve));
  }
}

std::map<std::string, std::string> PPSInfor::GetFaultCodeDescription() const {
  return fault_code_;
}

std::map<std::string, std::string> PPSInfor::GetFaultCodeResolve() const {
  return fault_resolve_;
}

std::map<std::string, std::string> PPSInfor::GetStateCode() const {
  return state_code_;
}
