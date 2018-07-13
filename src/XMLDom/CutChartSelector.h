// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include <list>
#include <string>
#include <vector>
#include <QtXml/QDomDocument>

struct CutChartSelectorAttr  {
	std::string field_name;
	bool is_keyword_;
};

class CutChartSelector {
 public:
  explicit CutChartSelector(const std::string &cut_chart_selector_file);

  std::size_t GetKeywordCount() const;

  std::vector<std::string> GetKeywordName() const;

  std::vector<std::string> GetKeywordList(const std::string &keyword_name,
      const std::vector<std::string> &selected_keywords) const;

  std::vector<std::string> GetCurrentSelectedCutChart() const;

  bool SetCurrentSelectedCutChart(const std::vector<std::string> &keywords);

 private:
  std::list<CutChartSelectorAttr> attr_;
  std::list<std::vector<std::string> > records_;
  QDomDocument doc_;
  std::string cut_chart_selector_file_;

}; // class CutChartSelector
