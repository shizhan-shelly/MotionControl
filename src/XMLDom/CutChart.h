// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTCHART_H__
#define CUTCHART_H__

#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <QtXml/QDomDocument>

typedef enum _DataType {
  Int = 0,
  Float,
  String,
  Bool,
  Enum,

} DataType;

typedef struct _CutChartAttr {
  std::string min_;
  std::string max_;
  std::string default_value_;
  std::string display_format_;
  DataType data_type;
  int wr_;
  int is_keyword_;

} CutChartAttr;

class CutChart {
 public:
  CutChart();
  ~CutChart();

  bool ParseCutChart(const std::string &cut_chart_file, const std::string &bak_cut_chart_file);

  bool GetKeywordFieldNameAndUnit(std::vector<std::pair<std::string, std::vector<std::string> > > &name_unit) const;

  std::vector<std::string> GetKeywordList(const std::string &keyword_name,
      const std::map<std::string, std::string> &selected_keywords) const;

  bool SetCurrentSelectedRecord(const std::map<std::string, std::string> &alias_value);
  bool SetCurrentSelectedRecord(const std::vector<std::string> &keyword_value);
  bool GetCurrentSelectedRecord(std::vector<std::string> &keyword_value) const;

  bool GetGeneralFieldNameAndUnit(std::vector<std::pair<std::string, std::vector<std::string> > > &name_unit) const;

  bool GetAllFieldNameAndUnit(std::vector<std::pair<std::string, std::vector<std::string> > > &name_unit) const;

  std::string GetItemValueByFieldName(const std::string &field_name) const;

  // Get all consumables name with a special record.
  std::vector<std::string> GetConsumables() const;

  CutChartAttr GetOneFieldAttr(const std::string &field_name) const;

  /**
   * Get system config information in CutChart.xml.
   * @return config infor as a vector of map.
   * The first string of the map is keyword field name of CutChartSelector,
   * the second of the map is keyword field value of CutChartSelector.
   * The config map infor can be found in CutChartList of CutChartSelector.xml
   */
  std::vector<std::map<std::string, std::string> > GetSystemConfig() const;

  std::string GetVendor() const;

  std::string GetVersion() const;

  // If this record existed, give a prompt that insert fialed,
  // if not existed, insert the record.
  // The first string is field name, the second is the value.
  // After insert, current keyword field's value is the just inserted object's.
  bool InsertRecord(const std::map<std::string, std::string> &record);
  // Delete the record of current selected keyword
  bool DeleteRecord();
  // Update current record value.
  // The first string is field name, the second is the value.
  bool UpdateRecord(const std::map<std::string, std::string> &record);
  // Restore one selected record in user doc from backup xml file.
  bool RevertRecord();

  bool SaveCutChart();

 private:
  std::vector<std::pair<std::string, std::string> > keyword_field_;
  QDomDocument doc_usr_;
  QDomDocument doc_fac_;
  std::string cut_chart_file_;

  void InitialKeywordField();
  QDomNode GetCurSelRecord(const QDomDocument &doc) const;
  // Judge the check string whether in the string list.
  bool hasRecord(const std::string &check, const std::vector<std::string> &list, DataType type);
  bool ParseToDoc(const std::string &xml_file, QDomDocument &doc);

}; // class CutChart

#endif // CUTCHART_H__
