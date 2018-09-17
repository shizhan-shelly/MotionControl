// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef LOGIC_ALIAS_H__
#define LOGIC_ALIAS_H__

#include <map>
#include <string>
#include <QtXml/QDomDocument>

class Alias {
 public:
  bool ParseAlias(const std::string &alias_file);

  std::map<std::string, std::string> GetAliasName(
      const std::string &process_type) const;

 private:
  QDomDocument doc_;
  std::string alias_file_;

  std::string GetAliasMap(const std::string &process_type) const;

}; // class Alias

#endif // LOGIC_ALIAS_H__
