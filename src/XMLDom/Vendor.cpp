// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "Vendor.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>

Vendor::Vendor(const std::string &vendor_file) {
  vendor_file_ = vendor_file;
  QFile file(vendor_file.c_str());
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  if (!doc_.setContent(&file)) {
    // TODO(zhanshi): write error log.
  }
  file.close();
}

std::string Vendor::GetVendorXMLVersion() const {
  return doc_.documentElement().attribute("Version").toStdString();
}

bool Vendor::GetVendorList(std::vector<std::string> &vendor_list) const {
  QDomElement	ele = doc_.documentElement().firstChildElement("VendorList");
  QDomNodeList child_nodes = ele.childNodes();
  for (int i = 0; i < child_nodes.size(); i++) {
    vendor_list.push_back(child_nodes.at(i).toElement().attribute("name").toStdString());
  }
  return true;
}

bool Vendor::SetCurrentSelectedVendor(const std::string &vendor_name) {
  QDomElement	ele = doc_.documentElement().firstChildElement("CurrentSelectVendor");
  ele.setAttribute("name", vendor_name.c_str());

  QFile file(vendor_file_.c_str());
  if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    return false;
  }
  QTextStream out(&file);
  doc_.save(out, 2);
  file.close();
  return true;
}

bool Vendor::GetCurrentSelectedVendor(std::string &vendor_name) const {
  QDomElement	ele = doc_.documentElement().firstChildElement("CurrentSelectVendor");
  vendor_name = ele.attribute("name").toStdString();
  return true;
}
