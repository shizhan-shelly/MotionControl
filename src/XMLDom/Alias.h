// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef LOGIC_ALIAS_H__
#define LOGIC_ALIAS_H__

#include <map>
#include <string>
#include <QtXml/QDomDocument>
#include <vector>

class Alias {
 public:
  bool ParseAlias(const std::string &alias_file);

  /**
   * Description:
   * Get field name and field value in cut chart.
   * It is used for select a cut chart data record.
   * @param [in]: process_type, alias table map in AliasCfg, like as "V507".
   * @param [in]: process_variable, variable after 'F' of G59 code.
   * @example, G59 V507 F10.000
   * process_type is "V507", process_variable is "10.000".
   */
  std::map<std::string, std::string> GetBaseName(
      const std::string &process_type,
      const std::string &process_variable) const;

  /**
   * Get all base name in one of alias list. It is used for selection of
   * insert data into cut chart data record.
   * @param [in]: alis_map, name of alias table. Like as "TorchType".
   * As usually, this is also just the keyword field name in cut chart.
   */
  std::vector<std::string> GetBaseName(
      const std::string &alias_map) const;

 private:
  QDomDocument doc_;
  std::string alias_file_;

}; // class Alias

#endif // LOGIC_ALIAS_H__
