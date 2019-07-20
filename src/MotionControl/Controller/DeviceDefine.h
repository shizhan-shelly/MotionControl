// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_DEVICEDEFINE_H__
#define CONTROLLER_DEVICEDEFINE_H__

#include <QString>

struct ConfigItem {
  QString name;
  QString group;
  QString index;
  QString no_nc;
};

struct ADItem {
  QString name;
  QString group;
  QString index;
};

struct DAItem {
  QString name;
  QString group;
  QString index;
  int threshold;
};

struct BoardItem {
  int group_;
  QString model_;
  QString addr_;
};

#endif // CONTROLLER_DEVICEDEFINE_H__
