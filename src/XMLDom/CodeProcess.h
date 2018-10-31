// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_PLASMA_LOGIC_CODEPROCESS_H__
#define CUTTER_WIDGET_PLASMA_LOGIC_CODEPROCESS_H__

#include <map>
#include <vector>

#include "../../../baseclass/gcodeparse/GCommand.h"

namespace cutter {

typedef enum _HyperthermTHCItem {
  SetArcVoltage = 600,
  PierceTime = 601,
  PierceHeightFactor = 602,
  CutHeight = 603,
  TransferHeightFactor = 604,
  CutHeightDelay = 605,
  KerfDetectReacquireTime = 606,
  ModeSelect = 607,
  ArcCurrent = 608,
  AVCDelay =613,

} HyperthermTHCItem;


class HyperthermCodeProcess {
 public:
  HyperthermCodeProcess();
  virtual ~HyperthermCodeProcess();

  // From current cut chart database.
  void InitialDefaultProcess();

  /**
   * @brief ParseGCode
   * @param g59_code, a process map:(V507, F33)
   */
  void ParseGCode(const std::map<std::string, std::string> &g59_code);

 private:
  std::map<std::string, std::string> keyword_infor_;
  std::map<HyperthermTHCItem, std::string> thc_item_;

}; // class HyperthermCodeProcess

} // namespace cutter

#endif // CUTTER_WIDGET_PLASMA_LOGIC_CODEPROCESS_H__
