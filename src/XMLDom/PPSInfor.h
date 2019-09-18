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

  /// This function can get pps infor from xml file.
  /// @example: pps_item, -- "FaultCode" / "StateCode";
  ///           infor_code, the value of "code"
  ///           infor_prefix_, prefix of pps infor -- "description"
  /// @return: pps infor value which user want.
  std::string GetPPSInfor(const std::string &pps_item,
                          const std::string &infor_code,
                          const std::string &infor_prefix_) const;

 private:
  QDomDocument doc_;
  std::string pps_infor_file_;

}; // class PPSInfor

#endif // PPSINFOR_H__
