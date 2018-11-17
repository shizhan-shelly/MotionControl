// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef KERFTABLE_KERFTABLEDLG_H__
#define KERFTABLE_KERFTABLEDLG_H__

#include "Widget/dialog/BaseDialog.h"

class KerfTableModel;
class QTableView;

class KerfTableDlg : public ::widget::BaseDialog {
 public:
  explicit KerfTableDlg(QWidget *parent = NULL);
  ~KerfTableDlg();

  void setModel(KerfTableModel *table_model);

 private:
  KerfTableModel *table_model_;
  QTableView *table_view_;

}; // class KerfTableDlg

#endif // KERFTABLE_KERFTABLEDLG_H__
