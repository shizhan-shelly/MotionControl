// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PPSINFOR_H__
#define PPSINFOR_H__

#include <map>
#include <string>
#include <QtCore/QVector>
#include <QtXml/QDomDocument>

class PPSInfor {
 public:
  PPSInfor();
  ~PPSInfor();

  bool ParsePPSInfor(const std::string &xml_file);

  /// This function can get pps infor from xml file.
  /// @example: pps_item, -- "FaultCode" / "StateCode";
  ///           attr_map, -- <model="HiFocus130">, <version="3.00">
  ///           infor_key, -- <code="200">
  ///           infor_prefix, prefix of pps infor -- "description"
  /// @return: pps infor value which user want.
  std::string GetPPSInfor(const std::string &pps_item,
                          const std::map<std::string, std::string> &attr_map,
                          const std::pair<std::string, int> &infor_key,
                          const std::string &infor_prefix) const;

  /// This function can get a serial string for same prefix from xml file.
  /// @example: pps_item, -- "FaultCode" / "StateCode";
  ///           attr_map, -- <model="HiFocus130">, <version="3.00">
  ///           infor_prefix, prefix of pps infor -- "description"
  /// @return: serial strings which user want.
  QVector<QString> GetPPSInfor(const std::string &pps_item,
      const std::map<std::string, std::string> &attr_map,
      const std::string &infor_prefix) const;

 private:
  QDomDocument doc_;
  std::string pps_infor_file_;

  QDomElement GetTargetNode(const std::string &pps_item,
      const std::map<std::string, std::string> &attr_map) const;

}; // class PPSInfor

#endif // PPSINFOR_H__
