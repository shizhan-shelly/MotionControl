// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CodeProcess.h"

#include "cutter/OCutter.h"

namespace cutter {

typedef std::pair<int, std::string> pair_t;

static const pair_t hypertherm_thc[] = {
  pair_t(600, "CuttingVoltage"),
  pair_t(601, "PierceTime"),
  pair_t(602, "PierceHeight"),
  pair_t(603, "CuttingHeight"),
  pair_t(604, "IgnitionHeight"),
  pair_t(605, "CutHeightDelay"),
  pair_t(606, "KerfRedetectTime"),
  pair_t(607, "ModeSelect"),
  pair_t(608, "ArcCurrent"),
  pair_t(613, "AVCDelay"),
};

static const std::map<int, std::string> HYPERTHERM_THC(hypertherm_thc,
    hypertherm_thc + sizeof(hypertherm_thc) / sizeof(hypertherm_thc[0]));

void HyperthermCodeProcess::ParseGCode(
    const std::map<std::string, std::string> &g59_code) {

  std::map<std::string, std::string> v500_code;
  std::map<std::string, std::string> v600_code;
  for (std::map<std::string, std::string>::const_iterator iter =
    g59_code.begin(); iter != g59_code.end(); iter++) {

    std::string process_type_str = GetCodeValue(iter->first, 'V');
    int process_type = atoi(process_type_str.c_str());
    std::string process_value = GetCodeValue(iter->second, 'F');
    if (process_type >= 500 && process_type < 600) {
      v500_code.insert(std::make_pair(process_type_str, process_value));
    } else if (process_type >= 600 && process_type < 700) {
      v600_code.insert(std::make_pair(process_type_str, process_value));
    }
  }

  std::map<std::string, std::string> keyword_infor;
  OCutter *cutter = OCutter::GetInstance();
  for (std::map<std::string, std::string>::iterator iter =
    v500_code.begin(); iter != v500_code.end(); iter++) {

    std::string variable_type = cutter->GetAlias()->GetAliasMap(iter->first);
    std::map<std::string, std::string> alias_base = cutter->GetAlias()->GetAliasName(variable_type);
    std::string variable_value = alias_base[iter->second];
    keyword_infor.insert(std::make_pair(variable_type, variable_value));
  }
  cutter->GetCutChart()->SetCurrentSelectedRecord(keyword_infor);

  // get thc parameters from cut chart
  thc_parameter_.clear();
  for (std::map<int, std::string>::const_iterator iter =
    HYPERTHERM_THC.begin(); iter != HYPERTHERM_THC.end(); iter++) {

    thc_parameter_.insert(std::make_pair(iter->second,
        cutter->GetCutChart()->GetItemValueByFieldName(iter->second)));

  }

  // modify thc parameters from G59 code
  for (std::map<std::string, std::string>::iterator iter =
    v600_code.begin(); iter != v600_code.end(); iter++) {

    std::map<int, std::string>::const_iterator iter1 = HYPERTHERM_THC.find(
        atoi(iter->first.c_str()));

    if (iter1 != HYPERTHERM_THC.end()) {
      std::map<std::string, std::string>::iterator iter2 = thc_parameter_.find(iter1->second);
      if (iter2 != thc_parameter_.end()) {
        iter2->second = iter->second;
      }
    }
  }
}

std::string CodeProcess::GetCodeValue(const std::string &code_line, char match) {
  std::size_t pos = code_line.find(match);
  if (pos == std::string::npos) {
    return "";
  }
  std::size_t end_pos = code_line.find_first_not_of("+-0123456789.e", pos + 1);
  std::string value_string = end_pos != std::string::npos ?
      code_line.substr(pos + 1, end_pos - pos -1) : code_line.substr(pos + 1);

  return value_string;
}

}
