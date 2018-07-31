// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CutChartSelector.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>

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

std::vector<std::string> CutChartSelector::GetKeywordName() const {
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

std::vector<std::string> CutChartSelector::GetCurrentSelectedCutChart() const {
  std::vector<std::string> result;
  QDomElement	selected_item = doc_.documentElement().firstChildElement("CurrentSelectCutChart");
  QDomNamedNodeMap node_map = selected_item.attributes();
  for (int i = 0; i < node_map.size(); i++) {
    result.push_back(node_map.item(i).nodeValue().toStdString());
  }
  return result;
}

bool CutChartSelector::SetCurrentSelectedCutChart(const std::vector<std::string> &keywords) {
  QDomElement	selected_item = doc_.documentElement().firstChildElement("CurrentSelectCutChart");
  QDomNamedNodeMap node_map = selected_item.attributes();
  for (int i = 0; i < node_map.size(); i++) {
    node_map.item(i).setNodeValue(keywords[i].c_str());
  }
  return WriteToXML();
}

std::string CutChartSelector::GetCutChartName() const {
  std::map<std::string, std::string> keyword_map;
  QDomElement	selected_item = doc_.documentElement().firstChildElement("CurrentSelectCutChart");
  QDomNamedNodeMap node_map = selected_item.attributes();
  for (int i = 0; i < node_map.size(); i++) {
    keyword_map.insert(std::make_pair(node_map.item(i).nodeName().toStdString(),
        node_map.item(i).nodeValue().toStdString()));

  }

  QDomElement	ele = doc_.documentElement().firstChildElement("CutChartList");
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
      return record_map.namedItem("CutChartName").nodeValue().toStdString();
    }
  }
  return "";
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
