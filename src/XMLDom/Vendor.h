// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef VENDOR_H__
#define VENDOR_H__

#include <string>
#include <vector>
#include <QtXml/QDomDocument>

/**
 * @brief Vendor
 *
 */
class Vendor {
 public:
  explicit Vendor(const std::string &vendor_file);

  std::string GetVendorXMLVersion() const;
  bool GetVendorList(std::vector<std::string> &vendor_list) const;
  bool SetCurrentSelectedVendor(const std::string &vendor_name);
  bool GetCurrentSelectedVendor(std::string &vendor_name) const;

 private:
  QDomDocument doc_;
  std::string vendor_file_;

}; // class Vendor

#endif // VENDOR_H__
