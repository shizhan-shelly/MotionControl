// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include <QtCore/QCoreApplication>

#include "Vendor.h"
#include "CutChartSelector.h"
#include "CutChart.h"
#include "Alias.h"
#include "PPSInfor.h"

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

  CutChartSelector cut_chart_selector;
  cut_chart_selector.ParseCutChartSelector("E:\\MyJob\\MotionControl\\tools\\Kjellberg\\CutChartSelector.xml");
  std::vector<std::string> cut_chart_selector_keyword_name = cut_chart_selector.GetKeywordFieldName();
  for (size_t i = 0; i < cut_chart_selector_keyword_name.size(); i++) {
    printf("%s\n", cut_chart_selector_keyword_name[i].c_str());
  }
  std::string cur_cut_chart_name;
  std::vector<std::string> current_cut_chart_selects = cut_chart_selector.GetCurrentSelectedCutChart(cur_cut_chart_name);
  for (size_t i = 0; i < current_cut_chart_selects.size(); i++) {
    printf("%s\t", current_cut_chart_selects[i].c_str());
  }
  std::vector<std::string> cut_chart_name = cut_chart_selector.GetCutChartNameList();
  for (size_t i = 0; i < cut_chart_name.size(); i++) {
    printf("\n%s\n", cut_chart_name[i].c_str());
  }

  std::vector<std::string> selected_keywords;
  selected_keywords.push_back("SF-120");
  std::vector<std::string> gas_box_list = cut_chart_selector.GetKeywordList(
      "GasBox", selected_keywords);

  for (size_t i = 0; i < gas_box_list.size(); i++) {
    printf("%s\t", gas_box_list[i].c_str());
  }

  std::vector<std::string> keywords;
  keywords.push_back("Smart Focus 130");
  keywords.push_back("PGV-300");
  keywords.push_back("PerCut2000");
  cur_cut_chart_name = "DB-PerCut_2000-Smart_Focus_130-PGV-300-Version3.xml";
  cut_chart_selector.SetCurrentSelectedCutChart(keywords, cur_cut_chart_name);

  cut_chart_selector.ImportCutChart("E:\\MyJob\\MotionControl\\tools\\Kjellberg\\DB-PerCut_2000-Smart_Focus_130-PGE-300-Version3.xml",
                                    "E:\\MyJob\\MotionControl\\tools\\Kjellberg\\DB-PerCut_2000-Smart_Focus_130-PGE-300-Version3.bml");

  CutChart cut_chart;
  cut_chart.ParseCutChart("E:\\MyJob\\MotionControl\\tools\\Kjellberg\\DB-PerCut_2000-Smart_Focus_130-PGE-300-Version3.xml",
                          "E:\\MyJob\\MotionControl\\tools\\Kjellberg\\DB-PerCut_2000-Smart_Focus_130-PGE-300-Version3.bml");
  std::vector<std::pair<std::string, std::vector<std::string> > > name_unit;
  cut_chart.GetKeywordFieldNameAndUnit(name_unit);
  for (size_t i = 0; i < name_unit.size(); i++) {
    printf("%s\t%s\n", name_unit[i].second[0].c_str(), name_unit[i].second[1].c_str());
  }
  printf("%s\n", cut_chart.GetItemValueByFieldName("CuttingSpeed").c_str());
  CutChartAttr attr = cut_chart.GetOneFieldAttr("Thickness");
  std::map<std::string, std::string> insert_record;
  insert_record.insert(std::make_pair("Material", "1.0037 S235"));
  insert_record.insert(std::make_pair("Thickness", "6.00"));
  insert_record.insert(std::make_pair("Current", "180.00"));
  insert_record.insert(std::make_pair("Technology", "Contour Cut Speed"));
  cut_chart.InsertRecord(insert_record);

  Alias alias;
  alias.ParseAlias("E:\\MyJob\\MotionControl\\tools\\Liuhe\\Alias.xml");
  alias.GetBaseName("V503", "1.99");
  alias.GetBaseName("Current");

  PPSInfor pps_infor;
  pps_infor.ParsePPSInfor("E:\\MyJob\\MotionControl\\tools\\Hypertherm\\PPSInfor.xml");
  std::string fault_resolve = pps_infor.GetPPSInfor("FaultCode", "110", "resolve");
  printf("%s\n", fault_resolve.c_str());

  return a.exec();
}
