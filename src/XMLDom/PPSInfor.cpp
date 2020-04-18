// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "PPSInfor.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>

inline double StringToDouble(QString str) {
  char *endPtr = NULL;
  double value = strtod(str.toStdString().c_str(), &endPtr);
  if (!std::string(endPtr).empty()) {
    value = 0.0;
  }
  return value;
}

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

std::string PPSInfor::GetPPSModel(
    const std::pair<std::string, int> &model_infor) {

  QDomElement dom = doc_.documentElement().firstChildElement("PPSModel");
  if (!dom.isNull()) {
    QDomNodeList records = dom.childNodes();
    for (int i = 0; i < records.size(); i++) {
      QDomNamedNodeMap node_map = records.item(i).attributes();
      QString node_value = node_map.namedItem(model_infor.first.c_str()).nodeValue();
      if (model_infor.second == node_value.toInt()) {
        return node_map.namedItem("model").nodeValue().toStdString();
      }
    }
  }
  return "";
}

std::string PPSInfor::GetPPSInfor(const std::string &pps_item,
    const std::map<std::string, std::string> &attr_map,
    const std::pair<std::string, int> &infor_key,
    const std::string &infor_prefix) const {

  QDomElement data_element = GetTargetNode(pps_item, attr_map);
  QDomNodeList records = data_element.childNodes();
  std::map<int, std::string> key_value;
  for (int i = 0; i < records.size(); i++) {
    QDomNamedNodeMap node_map = records.item(i).attributes();
    key_value.insert(std::make_pair(
        node_map.namedItem(infor_key.first.c_str()).nodeValue().toInt(),
        node_map.namedItem(infor_prefix.c_str()).nodeValue().toStdString()));

  }
  std::map<int, std::string>::iterator it = key_value.lower_bound(infor_key.second);
  if (it != key_value.end()) {
    return it->second;
  }
  return "";
}

std::string PPSInfor::GetPPSInfor(const std::string &pps_item,
    const std::map<std::string, std::string> &attr_map,
    const std::pair<std::string, double> &infor_key,
    const std::string &infor_prefix) const {

  QDomElement dom = GetTargetNode(pps_item, attr_map);
  if (!dom.isNull()) {
    QDomNodeList records = dom.childNodes();
    for (int i = 0; i < records.size(); i++) {
      QDomNamedNodeMap node_map = records.item(i).attributes();
      QString node_value = node_map.namedItem(infor_key.first.c_str()).nodeValue();
      double compare = StringToDouble(node_value) - infor_key.second;
      if (fabs(compare) < 0.05) {
        return node_map.namedItem(infor_prefix.c_str()).nodeValue().toStdString();
      }
    }
  }
  return "";
}

QVector<QString> PPSInfor::GetPPSInfor(const std::string &pps_item,
    const std::map<std::string, std::string> &attr_map,
    const std::string &infor_prefix) const {

  QVector<QString> result;
  QDomElement dom = GetTargetNode(pps_item, attr_map);
  if (!dom.isNull()) {
    QDomNodeList records = dom.childNodes();
    for (int i = 0; i < records.size(); i++) {
      QDomNamedNodeMap node_map = records.item(i).attributes();
      result.push_back(node_map.namedItem(infor_prefix.c_str()).nodeValue());
    }
  }
  return result;
}

QDomElement PPSInfor::GetTargetNode(const std::string &pps_item,
    const std::map<std::string, std::string> &attr_map) const {

  QDomElement dom = doc_.documentElement().firstChildElement(pps_item.c_str());
  if (dom.hasAttributes()) {
    std::map<std::string, std::string>::const_iterator it = attr_map.begin();
    while (!dom.isNull() && it != attr_map.end()) {
      QDomNamedNodeMap node_map = dom.attributes();
      QString attr_value = node_map.namedItem(it->first.c_str()).nodeValue();
      if (attr_value.indexOf(it->second.c_str()) == -1) {
        dom = dom.nextSiblingElement(pps_item.c_str());
        it = attr_map.begin();
        continue;
      }
      it++;
    }
  }
  return dom;
}
