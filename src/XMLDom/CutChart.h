// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTCHART_H__
#define CUTCHART_H__

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

  bool ParseCutChart(const std::string &cut_chart_file);

  bool GetKeywordFieldNameAndUnit(std::vector<std::pair<std::string, std::vector<std::string> > > &name_unit) const;

  std::vector<std::string> GetKeywordList(const std::string &keyword_name,
      const std::map<std::string, std::string> &selected_keywords);

  bool SetCurrentSelectedRecord(const std::map<std::string, std::string> &alias_value);
  bool SetCurrentSelectedRecord(const std::vector<std::string> &keyword_value);
  bool GetCurrentSelectedRecord(std::vector<std::string> &keyword_value) const;

  bool GetGeneralFieldNameAndUnit(std::vector<std::pair<std::string, std::vector<std::string> > > &name_unit) const;

  bool GetAllFieldNameAndUnit(std::vector<std::pair<std::string, std::vector<std::string> > > &name_unit) const;

  std::string GetItemValueByFieldName(const std::string &field_name) const;

  // Get all consumables name with a special record.
  std::vector<std::string> GetConsumables() const;

  CutChartAttr GetOneFieldAttr(const std::string &field_name) const;

  // If the record existed, give a prompt that insert fialed.
  // ���ݹؼ��ּ���Ƿ��Ѿ���������¼�ˣ�����оͱ���û������롣���ؼ������item����һ����¼������ֵ��
  // ��һ��string���ֶ������ڶ���string���ֶ�ֵ
  bool InsertRecord(const std::map<std::string, std::string> &record);
  // ɾ����ǰѡ��Ĺؼ��ֶ�Ӧ���м�¼
  bool DeleteRecord();
  // �����ֶ������������Ӧ���ֶ�ֵ����һ��string���ֶ������ڶ���string���ֶ�ֵ��
  bool UpdateRecord(const std::map<std::string, std::string> &record);
  // �ӱ����ļ��лָ������е�ֵ���ָ�ѡ�е�һ�е�����,
  bool RevertRecord();
  // �����и���ļ�
  bool SaveCutChart();

 private:
  std::vector<std::pair<std::string, std::string> > keyword_field_;
  QDomDocument doc_usr_;
  QDomDocument doc_fac_;
  std::string cut_chart_file_;

  void InitialKeywordField();
  QDomNode GetCurSelRecord() const;

}; // class CutChart

#endif // CUTCHART_H__
