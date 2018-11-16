// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "KerfTableDlg.h"

#include <assert.h>

#include <QtGui/QTableView>

#include "KerfTableModel.h"

KerfTableDlg::KerfTableDlg(QWidget *parent) : widget::BaseDialog(parent)
                                            , table_model_(NULL) {

  table_view_ = new QTableView(this);
  ui_->stack_widget_->addWidget(table_view_);
  ui_->stack_widget_->setCurrentWidget(table_view_);

  // connect signal and slot.
}

KerfTableDlg::~KerfTableDlg() {
  delete table_view_;
}

void KerfTableDlg::setModel(KerfTableModel *table_model) {
  assert(table_model);
  table_model_ = table_model;
  table_view_->setModel(table_model_);
  origin_kerf_value_ = table_model_->GetKerfTableValue();
}

void KerfTableDlg::OnConfirm() {
  QVector<double> kerf_value = table_model_->GetKerfTableValue();
  // save the table value.
}

void KerfTableDlg::OnCancel() {
  table_model_->initialKerfTableValue(origin_kerf_value_);
}
