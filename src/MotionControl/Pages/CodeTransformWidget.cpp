// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../Pages/CodeTransformWidget.h"

#include <assert.h>

#include <QtGui/QHeaderView>
#include <QtGui/QScrollBar>

#include "cutter/OCutter.h"
#include "cutter/ui_CodeTransformWidget.h"
#include "../Pages/CodeTransformModel.h"

namespace cutter {

CodeTransformWidget::CodeTransformWidget(QWidget *parent)
    : QWidget(parent)
    , model_(NULL) {

  ui_ = new Ui::CodeTransformWidget();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;"
                " font-family: SimSun }");

  initialWidget();
}

CodeTransformWidget::~CodeTransformWidget() {
  delete ui_;
}

void CodeTransformWidget::initialWidget() {
  ui_->table_view_->setSelectionMode(QAbstractItemView::SingleSelection);
  ui_->table_view_->setStyleSheet("QTableView { border: none; \
                                                background: transparent; \
                                                selection-background-color: #8EDE21; } \
                                   QHeaderView::section { background-color: lightblue; \
                                                          color: black; \
                                                          padding-left: 4px; \
                                                          border: 1px solid #6c6c6c;} \
                                   QScrollBar: vertical { width: 30px; }");

  model_ = OCutter::GetInstance()->GetCodeTransformModel();
  model_->initial();
  ui_->table_view_->setModel(model_);
  ui_->table_view_->verticalHeader()->setResizeMode(QHeaderView::Fixed);
  ui_->table_view_->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
  ui_->table_view_->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
  ui_->table_view_->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
  ui_->table_view_->horizontalHeader()->setResizeMode(3, QHeaderView::Stretch);
}

void CodeTransformWidget::insert() {
  assert(model_);
  QItemSelectionModel *select_model = ui_->table_view_->selectionModel();
  QModelIndexList indexes = select_model->selectedIndexes();
  if (!indexes.isEmpty()) {
    QModelIndex index = indexes.first();
    model_->insertRow(index.row());
  }
}

void CodeTransformWidget::remove() {
  assert(model_);
  QItemSelectionModel *select_model = ui_->table_view_->selectionModel();
  QModelIndexList indexes = select_model->selectedIndexes();
  if (!indexes.isEmpty()) {
    QModelIndex index = indexes.first();
    model_->removeRows(index.row(), indexes.count());
  }
}

} // namespace cutter
