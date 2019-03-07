// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "Nesting.h"

#include <algorithm>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>

Nesting::Nesting() {}

Nesting::~Nesting() {}

bool Nesting::ParseNesting(const std::string &xml_file) {
  nesting_file_ = xml_file;
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

bool Nesting::SetCurrentSelectedRecord(const std::map<std::string, std::string> &keyword_field) {
  QDomElement	selected_item = doc_.documentElement().firstChildElement("CurrentSelectCutChartRecord");
  QDomNamedNodeMap node_map = selected_item.attributes();
  std::map<std::string, std::string>::const_iterator iter = keyword_field.begin();
  for (; iter != keyword_field.end(); iter++) {
    node_map.namedItem(iter->first.c_str()).setNodeValue(iter->second.c_str());
  }
  return true;
}

std::vector<double> Nesting::GetInteriorProfileDiameter(
    const std::map<std::string, std::string> &keyword_field) const {

  std::vector<double> diameters;
  QDomElement data_element_ = doc_.documentElement().firstChildElement("CutChartData");
  QDomNodeList data_record_list = data_element_.childNodes();
  for (int i = 0; i < data_record_list.size(); i++) {
    QDomNode data_record = data_record_list.item(i);
    QDomNamedNodeMap node_map = data_record.attributes();
    QDomNode check_node = node_map.namedItem("ProfileType");
    QDomNode target_node = node_map.namedItem("Diameter");
    if (check_node.nodeValue().compare("I") == 0 && target_node.nodeValue().compare("*") != 0) {
      std::map<std::string, std::string>::const_iterator iter = keyword_field.begin();
      while (iter != keyword_field.end()) {
        QDomNode pre_node = node_map.namedItem(iter->first.c_str());
        if (pre_node.nodeValue().compare(iter->second.c_str()) != 0) {
          break;
        }
        iter++;
      }
      if (iter == keyword_field.end()) {
        diameters.push_back(target_node.nodeValue().toDouble());
      }
    }
  }
  SortNum(diameters);
  return diameters;
}

std::map<std::string, std::string> Nesting::GetInteriorProfileItemValue(
    const std::string &refer_diameter,
    const std::map<std::string, std::string> &keyword_field) const {

  QList<QDomNode> data_nodes;
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
      data_nodes.append(records.item(i));
    }
  }
  // Pick up target node from selected data nodes.
  std::map<std::string, std::string> nesting_data;
  if (!data_nodes.empty()) {
    foreach (QDomNode data_node, data_nodes) {
      QDomNamedNodeMap node_attr = data_node.attributes();
      if (node_attr.namedItem("ProfileType").nodeValue().compare("I") == 0 &&
          node_attr.namedItem("Diameter").nodeValue().compare(refer_diameter.c_str()) == 0) {

        nesting_data.insert(std::make_pair("CuttingSpeed", node_attr.namedItem("CuttingSpeed").nodeValue().toStdString()));
        nesting_data.insert(std::make_pair("LeadInSpeed", node_attr.namedItem("LeadInSpeed").nodeValue().toStdString()));
        nesting_data.insert(std::make_pair("Kerf", node_attr.namedItem("Kerf").nodeValue().toStdString()));
        nesting_data.insert(std::make_pair("DisableAHC", node_attr.namedItem("DisableAHC").nodeValue().toStdString()));
        nesting_data.insert(std::make_pair("AsynchronousStop", node_attr.namedItem("AsynchronousStop").nodeValue().toStdString()));
      }
    }
  }
  return nesting_data;
}

bool Nesting::SetInteriorProfileItemValue(
    const std::string &refer_diameter,
    const std::map<std::string, std::string> &modify_item,
    const std::map<std::string, std::string> &keyword_field) {

  QList<QDomNode> data_nodes;
  QDomElement data_element = doc_.documentElement().firstChildElement("CutChartData");
  QDomNodeList records = data_element.childNodes();
  for (int i = 0; i < records.size(); i++) {
    QDomNamedNodeMap node_map = records.item(i).attributes();
    std::map<std::string, std::string>::const_iterator iter =
        keyword_field.begin();

    bool check = true;
    for (; iter != keyword_field.end(); iter++) {
      if (node_map.namedItem(iter->first.c_str()).nodeValue().compare(
          iter->second.c_str()) != 0) {

        check = false;
        break;
      }
    }
    if (check) {
      data_nodes.append(records.item(i));
    }
  }
  // Pick up target node from selected data nodes.
  if (!data_nodes.empty()) {
    foreach (QDomNode data_node, data_nodes) {
      QDomNamedNodeMap node_attr = data_node.attributes();
      if (node_attr.namedItem("ProfileType").nodeValue().compare("I") == 0 &&
          node_attr.namedItem("Diameter").nodeValue().compare(refer_diameter.c_str()) == 0) {

        std::map<std::string, std::string>::const_iterator iter = modify_item.begin();
        for (; iter != modify_item.end(); iter++) {
          node_attr.namedItem(iter->first.c_str()).setNodeValue(iter->second.c_str());
        }
      }
    }
  }
  return true;
}

bool Nesting::SaveNesting() {
  QFile file(nesting_file_.c_str());
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    return false;
  }
  QTextStream out(&file);
  doc_.save(out, 2);
  file.close();
  return true;
}

void Nesting::SortNum(std::vector<double> &num) const {
  std::sort(num.begin(), num.end());
  std::vector<double>::iterator it = std::unique(num.begin(), num.end());
  num.resize(it - num.begin());
}
