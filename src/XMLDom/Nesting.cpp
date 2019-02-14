// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "Nesting.h"

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>

Nesting::Nesting() {}

Nesting::~Nesting() {}

bool Nesting::Parse(const std::string &xml_file) {
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

std::vector<std::string> Nesting::GetInteriorProfileDiameter(
    const std::map<std::string, std::string> &keyword_field) const {

  std::vector<std::string> diameters;
  QDomElement data_element_ = doc_.documentElement().firstChildElement("CutChartData");
  QDomNodeList data_record_list = data_element_.childNodes();
  for (int i = 0; i < data_record_list.size(); i++) {
    QDomNode data_record = data_record_list.item(i);
    QDomNamedNodeMap node_map = data_record.attributes();
    QDomNode target_node = node_map.namedItem("Diameter");
    if (!target_node.isNull()) {
      std::map<std::string, std::string>::const_iterator iter = keyword_field.begin();
      while (iter != keyword_field.end()) {
        QDomNode pre_node = node_map.namedItem(iter->first.c_str());
        if (pre_node.nodeValue().compare(iter->second.c_str()) != 0) {
          break;
        }
        iter++;
      }
      if (iter == keyword_field.end()) {
        diameters.push_back(target_node.nodeValue().toStdString());
      }
    }
  }
  return diameters;
}

std::string Nesting::GetItemValueByFieldName(const std::string &field_name,
    const std::string &refer_diameter,
    const std::map<std::string, std::string> &keyword_field) const {

  QDomNode data_node = QDomNode();
  QDomElement	data_element = doc_.documentElement().firstChildElement("CutChartData");
  QDomNodeList records = data_element.childNodes();
  for (int i = 0; i < records.size(); i++) {
    QDomNamedNodeMap node_map = records.item(i).attributes();
    std::map<std::string, std::string>::const_iterator iter =
        keyword_field.begin();

    for (; iter != keyword_field.end(); iter++) {
      if (node_map.namedItem(iter->first.c_str()).nodeValue().compare(
          iter->second.c_str()) != 0) {

        break;
      }
    }
    if (iter == keyword_field.end()) {
      data_node = records.item(i);
    }
  }
  if (!data_node.isNull()) {
    QDomNamedNodeMap node_map = data_node.attributes();
    QDomNode target_node = node_map.namedItem(field_name.c_str());
    if (!target_node.isNull()) {
      return target_node.nodeValue().toStdString();
    }
  }
  return "";
}
