// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include <QtCore/QCoreApplication>

#include "Vendor.h"
#include "CutChartSelector.h"

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

  CutChartSelector cut_chart_selector("E:\\MyJob\\MotionControl\\tools\\CutChartSelector.xml");
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

  return a.exec();
}
