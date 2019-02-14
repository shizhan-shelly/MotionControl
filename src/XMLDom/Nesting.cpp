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
    const std::map<std::string, std::string> &keyword_field_) const {
}

std::string Nesting::GetItemValueByFieldName(const std::string &field_name,
    const std::string &refer_diameter,
    const std::map<std::string, std::string> &keyword_field_) const {

}
