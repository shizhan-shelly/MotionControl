// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTTER_WIDGET_PLASMA_NESTINGDLG_H__
#define CUTTTER_WIDGET_PLASMA_NESTINGDLG_H__

#include "Widget/dialog/BaseDialog.h"

class QTableView;

namespace cutter {

class NestingModel;

class NestingDlg : public ::widget::BaseDialog {
 public:
  explicit NestingDlg(QWidget *parent = NULL);
  ~NestingDlg();

  void setModel(NestingModel *nesting_model);

 private:
  NestingModel *nesting_model_;
  QTableView *table_view_;

}; // class NestingDlg

} // namespace cutter

#endif // CUTTTER_WIDGET_PLASMA_NESTINGDLG_H__
