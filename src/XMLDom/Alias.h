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

  std::string GetAliasMap(const std::string &process_type) const;

  /**
   * Description:
   * This function will get a map of alias name and base name.
   * For exmaple: The Alias.xml is shown as follows.
   * <Alias Version="1.0" Vendor="Liuhe">
       <AliasCfg V502="TorchType" V501="PowerSupply"/>
       <AliasList>
         <PowerSupply>
           <Record base_name="LH270A" alias_name="1"/>
         </PowerSupply>
         <TorchType>
           <Record base_name="THERMACUT XD" alias_name="1"/>
           <Record base_name="THERMACUT XD Bevel" alias_name="2"/>
          </TorchType>
       </AliasList>
     </Alias>
   * @param [in]: alias_map, name of alias table. Like as "TorchType".
   * @return: Generate a map of <alias_name, base_name> for cut chart data
   * operation with specified alias table name.
   */
  std::map<std::string, std::string> GetAliasName(
      const std::string &alias_map) const;

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
