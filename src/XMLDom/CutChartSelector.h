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

  std::vector<std::string> GetKeywordName() const;

  std::vector<std::string> GetKeywordList(const std::string &keyword_name,
      const std::vector<std::string> &selected_keywords) const;

  std::vector<std::string> GetCurrentSelectedCutChart() const;

  bool SetCurrentSelectedCutChart(const std::vector<std::string> &keywords);

  std::string GetCutChartName() const;

 private:
  QDomDocument doc_;
  std::string cut_chart_selector_file_;

  bool WriteToXML();

}; // class CutChartSelector

#endif // CUTCHARTSELECTOR_H__
