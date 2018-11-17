// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CutChartSelector.h"

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>

#include "CutChart.h"

CutChartSelector::CutChartSelector(const std::string &cut_chart_selector_file) {
  cut_chart_selector_file_ = cut_chart_selector_file;
  QFile file(cut_chart_selector_file.c_str());
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString error_msg = "";
  int line = 0;
  int column = 0;
  if (!doc_.setContent(&file, &error_msg, &line, &column)) {
    // TODO(Zhan Shi): write error log.
  }
  file.close();
}

std::vector<std::string> CutChartSelector::GetKeywordFieldName() const {
  std::vector<std::string> result;
  QDomElement	ele = doc_.documentElement().firstChildElement("CutChartListAttr");
  QDomNodeList cut_chart_list_attr = ele.childNodes();
  for (int i = 0; i < cut_chart_list_attr.size(); i++) {
    QDomNode node = cut_chart_list_attr.item(i);
    if (node.isElement()) {
      if (node.toElement().attribute("IsKeyword").toInt() == 1) {
        result.push_back(node.toElement().attribute("DisplayName").toStdString());
      }
    }
  }
  return result;
}

std::vector<std::string> CutChartSelector::GetKeywordList(
    const std::string &keyword_name,
    const std::vector<std::string> &selected_keywords) const {

  std::vector<std::string> result;
  QDomElement	ele = doc_.documentElement().firstChildElement("CutChartList");
  QDomNodeList cut_chart_list = ele.childNodes();
  for (int i = 0; i < cut_chart_list.size(); i++) {
    QDomNode node = cut_chart_list.item(i);
    QDomNamedNodeMap node_map = node.attributes();
    QDomNode target_node = node_map.namedItem(keyword_name.c_str());
    if (!target_node.isNull()) {
      size_t i = selected_keywords.size() - 1;
      QDomNode pre_node = node_map.item(i);
      while (!pre_node.isNull() && i >= 0) {
        if (pre_node.nodeValue().compare(selected_keywords[i].c_str()) != 0) {
          break;
        }
        i--;
        pre_node = node_map.item(i);
      }
      if (i == -1) {
        result.push_back(target_node.nodeValue().toStdString());
      }
    }
  }
  return result;
}

std::vector<std::string> CutChartSelector::GetCurrentSelectedCutChart(
    std::string &cut_chart_name) const {

  std::vector<std::string> result;
  QDomElement	selected_item = doc_.documentElement().firstChildElement("CurrentSelectCutChart");
  QDomElement	attr_element = doc_.documentElement().firstChildElement("CutChartListAttr");
  QDomNodeList cut_chart_list_attr = attr_element.childNodes();
  for (int i = 0; i < cut_chart_list_attr.size(); i++) {
    QDomNode node = cut_chart_list_attr.item(i);
    if (node.isElement()) {
      QDomElement element = node.toElement();
      if (element.attribute("IsKeyword").toInt() == 1) {
        result.push_back(selected_item.attributes().namedItem(element.tagName()).nodeValue().toStdString());
      }
    }
  }
  cut_chart_name = selected_item.attributes().namedItem("CutChartName").nodeValue().toStdString();
  return result;
}

bool CutChartSelector::SetCurrentSelectedCutChart(const std::vector<std::string> &keywords,
                                                  const std::string &cut_chart_name) {

  QDomElement	selected_item = doc_.documentElement().firstChildElement("CurrentSelectCutChart");
  QDomElement	attr_element = doc_.documentElement().firstChildElement("CutChartListAttr");
  QDomNodeList cut_chart_list_attr = attr_element.childNodes();
  std::vector<std::string>::const_iterator iter = keywords.begin();
  for (int i = 0; i < cut_chart_list_attr.size(); i++) {
    QDomNode node = cut_chart_list_attr.item(i);
    if (node.isElement()) {
      QDomElement element = node.toElement();
      if (element.attribute("IsKeyword").toInt() == 1 && iter != keywords.end()) {
        selected_item.attributes().namedItem(element.tagName()).setNodeValue(iter->c_str());
        iter++;
      }
    }
  }
  selected_item.attributes().namedItem("CutChartName").setNodeValue(cut_chart_name.c_str());
  return WriteToXML();
}

std::vector<std::string> CutChartSelector::GetCutChartNameList() const {
  std::vector<std::string> cut_chart_name;
  std::map<std::string, std::string> keyword_map;
  QDomElement	selected_item = doc_.documentElement().firstChildElement("CurrentSelectCutChart");
  QDomNamedNodeMap node_map = selected_item.attributes();
  for (int i = 0; i < node_map.size(); i++) {
    keyword_map.insert(std::make_pair(node_map.item(i).nodeName().toStdString(),
        node_map.item(i).nodeValue().toStdString()));

  }
  QDomElement ele = doc_.documentElement().firstChildElement("CutChartList");
  QDomNodeList cut_chart_list = ele.childNodes();
  for (int i = 0; i < cut_chart_list.size(); i++) {
    QDomNode node = cut_chart_list.item(i);
    QDomNamedNodeMap record_map = node.attributes();
    std::map<std::string, std::string>::iterator iter = keyword_map.begin();
    while (iter != keyword_map.end()) {
      if (record_map.namedItem(iter->first.c_str()).nodeValue().compare(
          iter->second.c_str()) != 0) {

        break;
      }
      iter++;
    }
    if (iter == keyword_map.end()) {
      cut_chart_name.push_back(record_map.namedItem("CutChartName").nodeValue().toStdString());
    }
  }
  return cut_chart_name;
}

bool CutChartSelector::ImportCutChart(const std::string &cut_chart_file,
                                      const std::string &bak_cut_chart_file) {

  CutChart import_cut_chart;
  if (!import_cut_chart.ParseCutChart(cut_chart_file, bak_cut_chart_file)) {
    return false;
  }
  QString vendor_name = doc_.documentElement().attribute("Vendor");
  if (vendor_name.compare(import_cut_chart.GetVendor().c_str()) != 0) {
    return false;
  }
  QFileInfo file_info(cut_chart_file.c_str());
  QDomElement cut_chart_list = doc_.documentElement().firstChildElement("CutChartList");
  QDomNodeList list_nodes = cut_chart_list.childNodes();
  for (int i = 0; i < list_nodes.size(); i++) {
    QDomNode node = list_nodes.item(i);
    if (node.toElement().attribute("CutChartName").compare(file_info.fileName()) == 0) {
      return true;
    }
  }
  std::string cut_chart_version = import_cut_chart.GetVersion();
  std::vector<std::map<std::string, std::string> > config_vector = import_cut_chart.GetSystemConfig();
  for (size_t i = 0; i < config_vector.size(); i++) {
    if (CheckDuplicate(cut_chart_version, file_info.fileName().toStdString(), config_vector[i])) {
      continue;
    }
    QDomElement new_element = doc_.createElement("Record");
    QDomElement	attr_element = doc_.documentElement().firstChildElement("CutChartListAttr");
    QDomNodeList cut_chart_list_attr = attr_element.childNodes();
    for (int j = 0; j < cut_chart_list_attr.size(); j++) {
      QDomNode node = cut_chart_list_attr.item(j);
      if (node.isElement()) {
        QDomElement element = node.toElement();
        if (element.attribute("IsKeyword").toInt() == 1) {
          std::map<std::string, std::string>::iterator iter = config_vector[i].find(
              element.tagName().toStdString());

          if (iter == config_vector[i].end()) {
            return false;
          }
          new_element.setAttribute(element.tagName(), iter->second.c_str());
        }
      }
    }
    new_element.setAttribute("Version", cut_chart_version.c_str());
    new_element.setAttribute("CutChartName", file_info.fileName());
    cut_chart_list.appendChild(new_element);
  }
  return WriteToXML();
}

bool CutChartSelector::WriteToXML() {
  QFile file(cut_chart_selector_file_.c_str());
  if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    return false;
  }
  QTextStream out(&file);
  doc_.save(out, 2);
  file.close();
  return true;
}

bool CutChartSelector::CheckDuplicate(const std::string &version,
    const std::string &file_name,
    const std::map<std::string, std::string> &system_config) {

  QDomElement	list = doc_.documentElement().firstChildElement("CutChartList");
  QDomNodeList list_child = list.childNodes();
  for (int i = 0; i < list_child.count(); i++) {
    QDomNode cur_node = list_child.item(i);
    if (cur_node.isElement()) {
      QDomElement cur_element = cur_node.toElement();
      std::map<std::string, std::string>::const_iterator iter;
      for (iter = system_config.begin(); iter != system_config.end(); iter++) {
        if (cur_element.attribute(iter->first.c_str()).compare(iter->second.c_str()) != 0) {
          break;
        }
      }
      if (iter == system_config.end()) {
        QString origin_version = cur_element.attribute("Version");
        if (origin_version.compare(version.c_str()) < 0) {
          cur_element.setAttribute("Version", version.c_str());
          cur_element.setAttribute("CutChartName", file_name.c_str());
        }
        return true;
      }
    }
  }
  return false;
}
