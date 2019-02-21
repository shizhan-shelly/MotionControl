// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "cutter/widget/plasma/sync/NestingAssist.h"

#include "cutter/OCutter.h"

namespace cutter {

NestingAssist::NestingAssist() {}

NestingAssist::~NestingAssist() {}

void NestingAssist::GetHyperthermProcessParameter(
    double cur_diameter, double &feedrate, double &lead_in_feedrate,
    double &kerf, double &asynchronous_stop, int &disable_ahc, double &US) {

  OCutter *cutter = OCutter::GetInstance();
  std::map<std::string, std::string> keyword_filed;
  cutter->GetCutChart()->GetCurrentSelectedRecord(keyword_filed);
  std::vector<double> interior_profile_diameter =
      cutter->GetNesting()->GetInteriorProfileDiameter(keyword_filed);

  std::string refer_diameter = GetReferDiameter(cur_diameter, interior_profile_diameter);
  std::map<std::string, std::string> interior_profile_value =
      cutter->GetNesting()->GetInteriorProfileItemValue(refer_diameter, keyword_filed);

  feedrate = atof(interior_profile_value["CuttingSpeed"].c_str());
  lead_in_feedrate = atof(interior_profile_value["LeadInSpeed"].c_str());
  kerf = atof(interior_profile_value["Kerf"].c_str());
  asynchronous_stop = atof(interior_profile_value["AsynchronousStop"].c_str());
  asynchronous_stop = asynchronous_stop < 0 ? asynchronous_stop : -asynchronous_stop;
  disable_ahc = atoi(interior_profile_value["DisableAHC"].c_str());
  US = PI * cur_diameter / 4;
}

void NestingAssist::GetKjellbergProcessParameter(double hole_diameter,
    double &hole_speed, double &lead_in_speed, double &overburn_speed,
    double &hole_kerf, double &asynchronous_stop,
    double &US, double &PA) {

  OCutter *cutter = OCutter::GetInstance();
  double cutting_kerf_hole = atof(cutter->GetCutChart()->GetItemValueByFieldName("KerfHole").c_str());
  double cutting_kerf_quality = atof(cutter->GetCutChart()->GetItemValueByFieldName("Kerf").c_str());
  double cutting_speed_hole = atof(cutter->GetCutChart()->GetItemValueByFieldName("CuttingSpeedHole").c_str());
  double cutting_speed_quality = atof(cutter->GetCutChart()->GetItemValueByFieldName("CuttingSpeed").c_str());
  double thickness = atof(cutter->GetCutChart()->GetItemValueByFieldName("Thickness").c_str());
  double down_slope = atof(cutter->GetCutChart()->GetItemValueByFieldName("DownSlope").c_str());
  asynchronous_stop = atof(cutter->GetCutChart()->GetItemValueByFieldName("PlasmaOffTime").c_str());
  asynchronous_stop = asynchronous_stop < 0 ? asynchronous_stop : -asynchronous_stop;

  double N2 = hole_diameter / thickness;
  double N8 = cutting_kerf_hole;
  double N17 = cutting_kerf_quality;
  double N18 = N17 - N8;
  double N19 = ((N2 - 1) * N18) + N8;
  double N20 = ((0.8 - 1) * N18) + N8;
  if (N2 < 0.8) {
    hole_kerf = N20;
  } else {
    if (N2 > 2) {
      hole_kerf = N17;
    } else {
      hole_kerf = N19;
    }
  }
  double N3 = cutting_speed_hole;
  double N4 = cutting_speed_quality;
  double N5 = N4- N3;
  double N6 = ((0.8 - 1) * N5) + N3;
  double O2 = ((N2 - 1) * N5) + N3;
  if (N2 < 0.8) {
    hole_speed = N6;
  } else {
    if (N2 > 2) {
      hole_speed = N4;
    } else {
      hole_speed = O2;
    }
  }
  down_slope *= 1000; // unit: ms
  double DS = (down_slope / 60) * (hole_speed / 1000);
  double D33 = down_slope + 50;
  US = DS + (1.5 * cutting_kerf_hole);
  PA = (hole_speed / 60) * (D33 / 1000);

  lead_in_speed = hole_speed;
  overburn_speed = hole_speed;
}

std::string NestingAssist::GetReferDiameter(double cur_diameter,
    std::vector<double> selectable_diameter) const {

  // selectable_diameter vector has already been sorted by ASC.
  char refer_buf[] = "*";
  for (size_t i = 0; i < selectable_diameter.size(); i++) {
    if (IsLesser(selectable_diameter[i], cur_diameter) == 0) {
      sprintf(refer_buf, "%.1f", selectable_diameter[i]);
      break;
    }
  }
  return refer_buf;
}

} // namespace cutter
