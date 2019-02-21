// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_NESTINGASSIST_H__
#define DATABASE_PLASMACUTTECHNOLOGY_NESTINGASSIST_H__

#include "singleton/Singleton.h"

namespace cutter {

class NestingAssist : public Singleton {
  DECLARE_SINGLETON(NestingAssist)

 public:
  void GetHyperthermProcessParameter(
      double cur_diameter, double &feedrate, double &lead_in_feedrate,
      double &kerf, double &asynchronous_stop, int &disable_ahc, double &US);

  void GetKjellbergProcessParameter(double hole_diameter,
      double &hole_speed, double &lead_in_speed, double &overburn_speed,
      double &hole_kerf, double &asynchronous_stop,
      double &US, double &PA);

 private:
  NestingAssist();
  ~NestingAssist();

  std::string GetReferDiameter(double cur_diameter,
      std::vector<double> selectable_diameter) const;

}; // class NestingAssist

} // namespace cutter

#endif // DATABASE_PLASMACUTTECHNOLOGY_NESTINGASSIST_H__
