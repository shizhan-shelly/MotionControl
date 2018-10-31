// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CodeProcess.h"

#include "cutter/OCutter.h"

namespace cutter {

HyperthermCodeProcess::HyperthermCodeProcess() {}

HyperthermCodeProcess::~HyperthermCodeProcess() {}

void HyperthermCodeProcess::InitialDefaultProcess() {
  std::vector<std::pair<std::string, std::vector<std::string> > > keyword_name;
  std::vector<std::string> keyword_value;
  OCutter *cutter = OCutter::GetInstance();
  cutter->GetCutChart()->GetKeywordFieldNameAndUnit(keyword_name);
  cutter->GetCutChart()->GetCurrentSelectedRecord(keyword_value);



}

void HyperthermCodeProcess::ParseGCode(
    const std::map<std::string, std::string> &g59_code) {

  OCutter *cutter = OCutter::GetInstance();
  for (size_t i = 0; i < g59_code.size(); i++) {
    std::string keyword = cutter->GetAlias()->GetAliasMap(g59_code[i].first);
    std::string
  }
}

}
