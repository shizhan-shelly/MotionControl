// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "PPSInfor.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>

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
  file.close();
  return true;
}

std::string PPSInfor::GetPPSInfor(const std::string &pps_item,
    const std::string &infor_code,
    const std::string &infor_prefix_) const {

  QDomElement data_element = doc_.documentElement().firstChildElement(pps_item.c_str());
  QDomNodeList records = data_element.childNodes();
  for (int i = 0; i < records.size(); i++) {
    QDomNamedNodeMap node_map = records.item(i).attributes();
    std::string code = node_map.namedItem("code").nodeValue().toStdString();
    if (code.compare(infor_code) == 0) {
      return node_map.namedItem(infor_prefix_.c_str()).nodeValue().toStdString();
    }
  }
  return "";
}
