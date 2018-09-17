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

std::map<std::string, std::string> Alias::GetAliasName(
    const std::string &process_type) const {

  std::map<std::string, std::string> alias_base_name;
  QDomElement	list = doc_.documentElement().firstChildElement("AliasList");
  std::string alias_select = GetAliasMap(process_type);
  QDomNodeList node_list = list.firstChildElement(alias_select.c_str()).childNodes();
  for (int i = 0; i < node_list.size(); i++) {
    QDomNamedNodeMap map = node_list.item(i).attributes();
    QString alias_name = map.namedItem("alias_name").nodeValue();
    QString base_name = map.namedItem("base_name").nodeValue();
    alias_base_name.insert(std::make_pair<std::string, std::string>(
        alias_name.toStdString(), base_name.toStdString()));

  }
  return alias_base_name;
}

std::string Alias::GetAliasMap(const std::string &process_type) const {
  QDomElement	config = doc_.documentElement().firstChildElement("AliasCfg");
  return config.attribute(process_type.c_str()).toStdString();
}
