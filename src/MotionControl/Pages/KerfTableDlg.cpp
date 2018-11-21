// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "KerfTableDlg.h"

#include <assert.h>

#include <QtGui/QHeaderView>
#include <QtGui/QScrollBar>
#include <QtGui/QTableView>

#include "KerfTableModel.h"

KerfTableDlg::KerfTableDlg(QWidget *parent) : widget::BaseDialog(parent)
                                            , table_model_(NULL) {

  table_view_ = new QTableView(this);
  table_view_->setMinimumSize(400, 400);
  table_view_->setSelectionMode(QAbstractItemView::SingleSelection);
  table_view_->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                  "width: 30px;"
                                                  "}");

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

  table_view_->verticalHeader()->setResizeMode(QHeaderView::Fixed);
  table_view_->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
  table_view_->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
}
