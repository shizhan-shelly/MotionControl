// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTCHARTSELECTOR_H__
#define CUTCHARTSELECTOR_H__

#include <map>
#include <string>
#include <vector>
#include <QtXml/QDomDocument>

class CutChartSelector {
 public:
  explicit CutChartSelector(const std::string &cut_chart_selector_file);

  std::vector<std::string> GetKeywordFieldName() const;

  std::vector<std::string> GetKeywordList(const std::string &keyword_name,
      const std::vector<std::string> &selected_keywords) const;

  std::vector<std::string> GetCurrentSelectedCutChart(std::string &cut_chart_name) const;

  bool SetCurrentSelectedCutChart(const std::vector<std::string> &keywords,
                                  const std::string &cut_chart_name);

  std::vector<std::string> GetCutChartNameList() const;

  bool ImportCutChart(const std::string &cut_chart_file,
                      const std::string &bak_cut_chart_file);

 private:
  QDomDocument doc_;
  std::string cut_chart_selector_file_;

  // If duplicate, remain the item with last version in cut chart list.
  // If duplicate, return true; if not return false.
  bool CheckDuplicate(const std::string &version, const std::string &file_name,
      const std::map<std::string, std::string> &system_config);

  bool WriteToXML();

}; // class CutChartSelector

#endif // CUTCHARTSELECTOR_H__
