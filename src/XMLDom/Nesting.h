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

  bool ParseNesting(const std::string &xml_file);

  bool SetCurrentSelectedRecord(
      const std::map<std::string, std::string> &keyword_field);

  std::vector<double> GetInteriorProfileDiameter(
      const std::map<std::string, std::string> &keyword_field) const;

  std::map<std::string, std::string> GetInteriorProfileItemValue(
      const std::string &refer_diameter,
      const std::map<std::string, std::string> &keyword_field) const;

  bool SetInteriorProfileItemValue(
      const std::string &refer_diameter,
      const std::map<std::string, std::string> &modify_item,
      const std::map<std::string, std::string> &keyword_field);

  bool SaveNesting();

 private:
  QDomDocument doc_;
  std::string nesting_file_;

  void SortNum(std::vector<double> &num) const;

}; // class Nesting

#endif // NESTING_H__
