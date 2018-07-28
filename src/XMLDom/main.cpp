// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include <QtCore/QCoreApplication>

#include "Vendor.h"
#include "CutChartSelector.h"
#include "CutChart.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  Vendor vendor("E:\\MyJob\\MotionControl\\tools\\Vendor.xml");
  std::string cur_vendor = "";
  vendor.GetCurrentSelectedVendor(cur_vendor);
  printf("%s    %s\n", vendor.GetVendorXMLVersion().c_str(), cur_vendor.c_str());
  std::vector<std::string> vendor_list;
  vendor.GetVendorList(vendor_list);
  for (size_t i = 0; i < vendor_list.size(); i++) {
    printf("%s\n", vendor_list[i].c_str());
  }

  CutChartSelector cut_chart_selector("E:\\MyJob\\MotionControl\\tools\\Kjellberg\\CutChartSelector.xml");
  std::vector<std::string> cut_chart_selector_keyword_name = cut_chart_selector.GetKeywordName();
  for (size_t i = 0; i < cut_chart_selector_keyword_name.size(); i++) {
    printf("%s\n", cut_chart_selector_keyword_name[i].c_str());
  }
  std::vector<std::string> current_cut_chart_selects = cut_chart_selector.GetCurrentSelectedCutChart();
  for (size_t i = 0; i < current_cut_chart_selects.size(); i++) {
    printf("%s\t", current_cut_chart_selects[i].c_str());
  }
  printf("\n\n");

  std::vector<std::string> selected_keywords;
  selected_keywords.push_back("SF-120");
  std::vector<std::string> gas_box_list = cut_chart_selector.GetKeywordList(
      "GasBox", selected_keywords);

  for (size_t i = 0; i < gas_box_list.size(); i++) {
    printf("%s\t", gas_box_list[i].c_str());
  }

  std::vector<std::string> keywords;
  keywords.push_back("SF-120");
  keywords.push_back("PGV-300");
  keywords.push_back("PerCut2500");
  cut_chart_selector.SetCurrentSelectedCutChart(keywords);

  CutChart cut_chart;
  cut_chart.ParseCutChart("E:\\MyJob\\MotionControl\\tools\\Kjellberg\\DB-PerCut_2000-Smart_Focus_130-PGE-300-Version3.xml");
  std::vector<std::pair<std::string, std::vector<std::string> > > name_unit;
  cut_chart.GetKeywordFieldNameAndUnit(name_unit);
  for (size_t i = 0; i < name_unit.size(); i++) {
    printf("%s\t%s\n", name_unit[i].second[0].c_str(), name_unit[i].second[1].c_str());
  }
  printf("%s\n", cut_chart.GetItemValueByFieldName("CuttingSpeed").c_str());
  CutChartAttr attr = cut_chart.GetOneFieldAttr("Thickness");
  return a.exec();
}
