// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef NESTING_H__
#define NESTING_H__

#include <map>
#include <string>
#include <vector>
#include <QtXml/QDomDocument>

class Nesting {
 public:
  Nesting();
  ~Nesting();

  bool Parse(const std::string &xml_file);

  std::vector<std::string> GetInteriorProfileDiameter(
      const std::map<std::string, std::string> &keyword_field) const;

  std::string GetItemValueByFieldName(const std::string &field_name,
      const std::string &refer_diameter,
      const std::map<std::string, std::string> &keyword_field) const;

 private:
  QDomDocument doc_;

}; // class Nesting

#endif // NESTING_H__
