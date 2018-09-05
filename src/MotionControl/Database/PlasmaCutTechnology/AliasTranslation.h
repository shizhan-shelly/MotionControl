// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_ALIASTRANSLATION_H__
#define DATABASE_ALIASTRANSLATION_H__

#include "base/singleton/Singleton.h"

#include <QtCore/QString.h>

class AliasTranslation : public Singleton {
  DECLARE_SINGLETON(AliasTranslation)

 public:
  QString Tr(const QString &origin_name);

 private:
  AliasTranslation();
  ~AliasTranslation();

}; // class AliasTranslation

#endif // DATABASE_ALIASTRANSLATION_H__
