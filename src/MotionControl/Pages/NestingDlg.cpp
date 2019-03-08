// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "NestingDlg.h"

#include <assert.h>

#include <QtGui/QHeaderView>
#include <QtGui/QScrollBar>
#include <QtGui/QTableView>

#include "NestingModel.h"

NestingDlg::NestingDlg(QWidget *parent) : widget::BaseDialog(parent)
                                        , nesting_model_(NULL) {

  table_view_ = new QTableView(this);
  table_view_->setMinimumSize(500, 400);
  table_view_->setSelectionMode(QAbstractItemView::SingleSelection);
  table_view_->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                  "width: 30px;"
                                                  "}");

  ui_->stack_widget_->addWidget(table_view_);
  ui_->stack_widget_->setCurrentWidget(table_view_);

  //connect(buttons(), SIGNAL(confirmed()), this, SLOT(OnConfirm()));
  //connect(buttons(), SIGNAL(canceled()), this, SLOT(OnCancel()));
}

NestingDlg::~NestingDlg() {
  delete table_view_;
}

void NestingDlg::setModel(NestingModel *nesting_model) {
  assert(nesting_model);
  nesting_model_ = nesting_model;
  table_view_->setModel(nesting_model_);

  table_view_->verticalHeader()->setResizeMode(QHeaderView::Fixed);
  for (int i = 0; i < nesting_model_->columnCount(); i++) {
    table_view_->horizontalHeader()->setResizeMode(i, QHeaderView::Stretch);
  }
}
