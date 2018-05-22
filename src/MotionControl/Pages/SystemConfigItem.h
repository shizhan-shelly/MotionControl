// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef SYSTEMCONFIGITEM_H__
#define SYSTEMCONFIGITEM_H__

#include <vector>

class SystemConfigItem {
 public :
  SystemConfigItem();
  virtual ~SystemConfigItem();

  void Append(const std::string &item);

  std::string GetItemElement(int column) const;

 private:
  std::vector<std::string> item_element_;

}; // class SystemConfigItem

#endif // SYSTEMCONFIGITEM_H__
