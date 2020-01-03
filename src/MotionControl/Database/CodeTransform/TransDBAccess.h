// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_CODETRANSFORM_TRANSDBACCESS_H__
#define DATABASE_CODETRANSFORM_TRANSDBACCESS_H__

#include <map>
#include <QtCore/QList>

#include "../SQLiteAccess.h"

class TransDBAccess : public SQLiteAccess {
 public:
  TransDBAccess();
  ~TransDBAccess();

  /**
   * @brief CodeMapping
   * @param system, example: ECKELMANN
   * @return code transform map, example: <"M14", "M07">
   * M14, the code which will be transformed from
   * M07, the code which will be transformed to
   */
  std::map<std::string, std::string> CodeMapping(const std::string &system);

  QList<std::map<std::string, std::string> > QueryAll(
      const std::string &system);

  bool ReplaceAll(const QList<std::map<std::string, std::string> > &new_data,
      const std::string &system);

}; // class TransDBAccess

#endif // DATABASE_CODETRANSFORM_TRANSDBACCESS_H__
