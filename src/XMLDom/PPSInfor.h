// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PPSINFOR_H__
#define PPSINFOR_H__

#include <map>
#include <string>
#include <QtXml/QDomDocument>

class PPSInfor {
 public:
  PPSInfor();
  ~PPSInfor();

  bool ParsePPSInfor(const std::string &xml_file);

  std::map<std::string, std::string> GetFaultCodeDescription() const;

  std::map<std::string, std::string> GetFaultCodeResolve() const;

  std::map<std::string, std::string> GetStateCode() const;

 private:
  QDomDocument doc_;
  std::string pps_infor_file_;
  std::map<std::string, std::string> fault_code_;
  std::map<std::string, std::string> fault_resolve_;
  std::map<std::string, std::string> state_code_;

  void ParseStateCode();
  void ParseFaultCode();

}; // class PPSInfor

#endif // PPSINFOR_H__
