// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_PLASMA_SYNC_CODEPROCESS_H__
#define CUTTER_WIDGET_PLASMA_SYNC_CODEPROCESS_H__

#include <map>

namespace cutter {

class CodeProcess {
 public:
  CodeProcess() {}
  virtual ~CodeProcess() {}

  void GenerateNMLMessage(int job_id);

  /**
   * @brief ParseGCode
   * @param g59_code, a process map:(V507, F33)
   */
  virtual void ParseGCode(const std::map<std::string, std::string> &g59_code) = 0;

 protected:
  // first string: field name; second string, field value.
  std::map<std::string, std::string> thc_parameter_;

  std::string GetCodeValue(const std::string &code_line, char match);

}; // class CodeProcess

class HyperthermCodeProcess : public CodeProcess {
 public:
  virtual void ParseGCode(const std::map<std::string, std::string> &g59_code);

}; // class HyperthermCodeProcess

} // namespace cutter

#endif // CUTTER_WIDGET_PLASMA_SYNC_CODEPROCESS_H__
