// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CutChart.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>

CutChart::CutChart() {}

CutChart::~CutChart() {}

bool CutChart::ParseCutChart(const std::string &cut_chart_file) {
  cut_chart_file_ = cut_chart_file;
  QFile file(cut_chart_file.c_str());
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }
  QString error_msg = "";
  int line = 0;
  int column = 0;
  if (!doc_usr_.setContent(&file, &error_msg, &line, &column)) {
    // TODO(Zhan Shi): write error log.
    file.close();
    return false;
  }
  file.close();
  InitialKeywordField();
  return true;
}

bool CutChart::GetKeywordFieldNameAndUnit(
    std::vector<std::pair<std::string, std::vector<std::string> > > &name_unit) const {

  QDomElement	attr_element = doc_usr_.documentElement().firstChildElement("CutChartAttr");
  QDomNodeList cut_chart_attr = attr_element.childNodes();
  for (int i = 0; i < cut_chart_attr.size(); i++) {
    QDomNode node = cut_chart_attr.item(i);
    if (node.isElement()) {
      QDomElement element = node.toElement();
      if (element.attribute("IsKeyword").toInt() == 1) {
        std::vector<std::string> infor;
        infor.push_back(element.attribute("NameText").toStdString());
        infor.push_back(element.attribute("UnitText").toStdString());
        name_unit.push_back(std::make_pair(element.tagName().toStdString(), infor));
      }
    }
  }
  return true;
}

std::vector<std::string> CutChart::GetKeywordList(const std::string &keyword_name,
    const std::map<std::string, std::string> &selected_keywords) {

  std::vector<std::string> result;
  QDomElement data_element_ = doc_usr_.documentElement().firstChildElement("CutChartData");
  QDomNodeList data_record_list = data_element_.childNodes();
  for (int i = 0; i < data_record_list.size(); i++) {
    QDomNode data_record = data_record_list.item(i);
    QDomNamedNodeMap node_map = data_record.attributes();
    QDomNode target_node = node_map.namedItem(keyword_name.c_str());
    if (!target_node.isNull()) {
      std::map<std::string, std::string>::const_iterator iter = selected_keywords.begin();
      while (iter != selected_keywords.end()) {
        QDomNode pre_node = node_map.namedItem(iter->first.c_str());
        if (pre_node.nodeValue().compare(iter->second.c_str()) != 0) {
          break;
        }
        iter++;
      }
      if (iter == selected_keywords.end()) {
        result.push_back(target_node.nodeValue().toStdString());
      }
    }
  }
  return result;
}

bool CutChart::SetCurrentSelectedRecord(const std::vector<std::string> &keyword_value) {
  QDomElement	selected_item = doc_usr_.documentElement().firstChildElement("CurrentSelectCutChartRecord");
  QDomNamedNodeMap node_map = selected_item.attributes();
  for (size_t i = 0; i < keyword_field_.size(); i++) {
    node_map.namedItem(keyword_field_[i].first.c_str()).setNodeValue(keyword_value[i].c_str());
  }
  InitialKeywordField();
  return true;
}

bool CutChart::GetCurrentSelectedRecord(std::vector<std::string> &keyword_value) const {
  for (size_t i = 0; i < keyword_field_.size(); i++) {
    keyword_value.push_back(keyword_field_[i].second);
  }
  return true;
}

bool CutChart::GetGeneralFieldNameAndUnit(std::vector<std::pair<std::string, std::vector<std::string> > > &name_unit) const {
  QDomElement	attr_element = doc_usr_.documentElement().firstChildElement("CutChartAttr");
  QDomNodeList cut_chart_attr = attr_element.childNodes();
  for (int i = 0; i < cut_chart_attr.size(); i++) {
    QDomNode node = cut_chart_attr.item(i);
    if (node.isElement()) {
      QDomElement element = node.toElement();
      if (element.attribute("Group").toInt() == 1) {
        std::vector<std::string> infor;
        infor.push_back(element.attribute("NameText").toStdString());
        infor.push_back(element.attribute("UnitText").toStdString());
        name_unit.push_back(std::make_pair(element.tagName().toStdString(), infor));
      }
    }
  }
  return true;
}

bool CutChart::GetAllFieldNameAndUnit(std::vector<std::pair<std::string, std::vector<std::string> > > &name_unit) const {
  QDomElement	attr_element = doc_usr_.documentElement().firstChildElement("CutChartAttr");
  QDomNodeList cut_chart_attr = attr_element.childNodes();
  for (int i = 0; i < cut_chart_attr.size(); i++) {
    QDomNode node = cut_chart_attr.item(i);
    if (node.isElement()) {
      QDomElement element = node.toElement();
      std::vector<std::string> infor;
      infor.push_back(element.attribute("NameText").toStdString());
      infor.push_back(element.attribute("UnitText").toStdString());
      name_unit.push_back(std::make_pair(element.tagName().toStdString(), infor));
    }
  }
  return true;
}

std::string CutChart::GetItemValueByFieldName(const std::string &field_name) const {
  QDomNode data_node = GetCurSelRecord();
  if (!data_node.isNull()) {
    QDomNamedNodeMap node_map = data_node.attributes();
    QDomNode target_node = node_map.namedItem(field_name.c_str());
    if (!target_node.isNull()) {
      return target_node.nodeValue().toStdString();
    }
  }
  return "";
}

std::vector<std::string> CutChart::GetConsumables() const {
  std::vector<std::string> result;
  QDomNode data_node = GetCurSelRecord();
  QDomElement	attr_element = doc_usr_.documentElement().firstChildElement("CutChartAttr");
  QDomNodeList cut_chart_attr = attr_element.childNodes();
  for (int i = 0; i < cut_chart_attr.size(); i++) {
    QDomNode node = cut_chart_attr.item(i);
    if (node.isElement()) {
      QDomElement element = node.toElement();
      if (element.attribute("Group").toInt() == 2) {
        result.push_back(data_node.toElement().attribute(element.tagName(),
            element.attribute("Default")).toStdString());

      }
    }
  }
  return result;
}

CutChartAttr CutChart::GetOneFieldAttr(const std::string &field_name) const {
  QDomElement	attr_element = doc_usr_.documentElement().firstChildElement("CutChartAttr");
  QDomElement cut_chart_attr = attr_element.firstChildElement(field_name.c_str());
  CutChartAttr attr;
  attr.data_type = cut_chart_attr.attribute("DataType").toInt();
  attr.min_ = cut_chart_attr.attribute("Min").toStdString();
  attr.max_ = cut_chart_attr.attribute("Max").toStdString();
  attr.default_value_ = cut_chart_attr.attribute("Default").toStdString();
  attr.display_format_ = cut_chart_attr.attribute("DisplayFormat").toStdString();
  attr.wr_ = cut_chart_attr.attribute("WR").toInt();
  attr.is_keyword_ = cut_chart_attr.attribute("IsKeyword").toInt();
  return attr;
}

bool CutChart::InsertRecord(const std::map<std::string, std::string> &record) {
  //1, 一一比对关键字的值，看看是否有重复的记录，重复报错
  //2，找到插入的位置插入一条记录
  //for (size_t i = 0; i < keyword_field_.size(); i++) {
  //  if () {
  //  }
  //}
  return true;
}

void CutChart::DeleteRecord() {
  QDomNode cur_node = GetCurSelRecord();
  if (!cur_node.isNull()) {
    doc_usr_.documentElement().firstChildElement("CutChartData").removeChild(cur_node);
  }
}

bool CutChart::UpdateRecord(const std::map<std::string, std::string> &record) {
  QDomNode cur_node = GetCurSelRecord();
  if (!cur_node.isNull()) {
    std::map<std::string, std::string>::const_iterator iter = record.begin();
    while (iter != record.end()) {
      cur_node.attributes().namedItem(iter->first.c_str()).setNodeValue(iter->second.c_str());
      iter++;
    }
    return true;
  }
  return false;
}

bool CutChart::RevertRecord() {
  return true;
}

bool CutChart::SaveCutChart() {
  QFile file(cut_chart_file_.c_str());
  if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    return false;
  }
  QTextStream out(&file);
  doc_usr_.save(out, 2);
  file.close();
  return true;
}

void CutChart::InitialKeywordField() {
  keyword_field_.clear();
  QDomElement	selected_element = doc_usr_.documentElement().firstChildElement("CurrentSelectCutChartRecord");
  QDomElement	attr_element = doc_usr_.documentElement().firstChildElement("CutChartAttr");
  QDomNodeList cut_chart_attr = attr_element.childNodes();
  for (int i = 0; i < cut_chart_attr.size(); i++) {
    QDomNode attr_node = cut_chart_attr.item(i);
    if (attr_node.isElement()) {
      QDomElement element = attr_node.toElement();
      if (element.attribute("IsKeyword").toInt() == 1) {
        QString field_name = element.tagName();
        keyword_field_.push_back(std::make_pair(field_name.toStdString(),
            selected_element.attributes().namedItem(field_name).nodeValue().toStdString()));

      }
    }
  }
}

QDomNode CutChart::GetCurSelRecord() const {
  QDomElement	data_element = doc_usr_.documentElement().firstChildElement("CutChartData");
  QDomNodeList records = data_element.childNodes();
  for (int i = 0; i < records.size(); i++) {
    QDomNamedNodeMap node_map = records.item(i).attributes();
    std::vector<std::pair<std::string, std::string> >::const_iterator iter =
        keyword_field_.begin();

    for (; iter != keyword_field_.end(); iter++) {
      if (node_map.namedItem(iter->first.c_str()).nodeValue().compare(
          iter->second.c_str()) != 0) {

        break;
      }
    }
    if (iter == keyword_field_.end()) {
      return records.item(i);
    }
  }
  return QDomNode();
}
