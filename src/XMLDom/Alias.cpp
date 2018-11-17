// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "Alias.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>

bool Alias::ParseAlias(const std::string &alias_file) {
  QFile file(alias_file.c_str());
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

std::map<std::string, std::string> Alias::GetBaseName(
    const std::string &process_type,
    const std::string &process_variable) const {

  std::map<std::string, std::string> result;
  QDomElement	config = doc_.documentElement().firstChildElement("AliasCfg");
  QString config_map = config.attribute(process_type.c_str());

  QDomElement	list = doc_.documentElement().firstChildElement("AliasList");
  QDomElement target_node = list.firstChildElement(config_map);
  QDomNodeList node_list = target_node.childNodes();
  for (int i = 0; i < node_list.size(); i++) {
    if (node_list.item(i).attributes().namedItem("alias_name").nodeValue().compare(
        process_variable.c_str()) == 0) {

      if (target_node.hasAttribute("second_level")) {
        result.insert(std::make_pair(config_map.toStdString(),
            node_list.item(i).attributes().namedItem("type1").nodeValue().toStdString()));

        result.insert(std::make_pair(target_node.attribute("second_level").toStdString(),
            node_list.item(i).attributes().namedItem("type2").nodeValue().toStdString()));

      } else {
        result.insert(std::make_pair(config_map.toStdString(),
            node_list.item(i).attributes().namedItem("base_name").nodeValue().toStdString()));

      }
      break;
    }
  }
  return result;
}

std::vector<std::string> Alias::GetBaseName(
    const std::string &alias_map) const {

  std::vector<std::string> base_names;
  QDomElement list = doc_.documentElement().firstChildElement("AliasList");
  QDomNodeList node_list = list.firstChildElement(alias_map.c_str()).childNodes();
  for (int i = 0; i < node_list.size(); i++) {
    QDomNamedNodeMap map = node_list.item(i).attributes();
    QString base_name = map.namedItem("base_name").nodeValue();
    base_names.push_back(base_name.toStdString());
  }
  return base_names;
}
