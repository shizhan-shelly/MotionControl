// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/widgets/extendedio/ExtendedIOConfigWidget.h"

#include <assert.h>

#include <QtGui/QHeaderView>
#include <QtGui/QScrollBar>

#include "ui_ExtendedIOConfigWidget.h"
#include "widget/delegate/ComboBoxDelegate.h"
#include "MotionControl/widgets/extendedio/ExtendedBoardModel.h"

ExtendedIOConfigWidget::ExtendedIOConfigWidget(QWidget *parent)
    : QWidget(parent)
    , dirty_(false)
    , extended_board_model_(NULL)
    , model_delegate_(NULL) {

  ui_ = new Ui::ExtendedIOConfigWidget();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;"
                " font-family: SimSun }");

  initialConfigWidget();
}

ExtendedIOConfigWidget::~ExtendedIOConfigWidget() {
  delete ui_;
}

void ExtendedIOConfigWidget::initialConfigWidget() {
  model_delegate_ = new widget::ComboBoxDelegate(this);
  QStringList board_model;
  board_model << "None" << "FCB1200PC" << "FCB1200PC_EXP" << "FCB1200PC_PANEL";
  model_delegate_->initialDelegate(board_model);

  ui_->edit_view_->setSelectionMode(QAbstractItemView::SingleSelection);
  ui_->edit_view_->setStyleSheet("QTableView { border: none; \
                                               background: transparent; \
                                               selection-background-color: #8EDE21; } \
                                  QHeaderView::section { background-color: lightblue; \
                                                         color: black; \
                                                         padding-left: 4px; \
                                                         border: 1px solid #6c6c6c;} \
                                  QScrollBar: vertical { width: 30px; }");

}

void ExtendedIOConfigWidget::setModel(ExtendedBoardModel *model) {
  assert(model);
  extended_board_model_ = model;
  ui_->edit_view_->setModel(extended_board_model_);
  ui_->edit_view_->setItemDelegateForColumn(1, model_delegate_);
  ui_->edit_view_->verticalHeader()->setResizeMode(QHeaderView::Fixed);
  ui_->edit_view_->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
  ui_->edit_view_->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
  ui_->edit_view_->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
  connect(extended_board_model_, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
      this, SLOT(onDataChanged(QModelIndex, QModelIndex)));

}

bool ExtendedIOConfigWidget::isDirty() {
  return dirty_;
}

bool ExtendedIOConfigWidget::isValid() {
  return true;
}

void ExtendedIOConfigWidget::commit() {
  QVector<BoardItem> board_items = extended_board_model_->GetExtendedBoard();
  // TODO(ZhanShi): commit modification to parameter XML.
  dirty_ = false;
}

void ExtendedIOConfigWidget::revert() {
  // TODO(ZhanShi): reset model to original.
  dirty_ = false;
}

void ExtendedIOConfigWidget::onDataChanged(const QModelIndex &topLeft,
    const QModelIndex &bottomRight) {

  assert(topLeft == bottomRight);
  Q_UNUSED(bottomRight);
  int row = topLeft.row();
  int column = topLeft.column();
  QVector<BoardItem> board_items = extended_board_model_->GetExtendedBoard();
  if (column == 1) {
    std::string origin_model = "";
    std::string new_model = board_items[row].model_.toStdString();
    if (origin_model.compare(new_model) != 0) {
      dirty_ = true;
    }
  } else if (column == 2) {
    std::string origin_addr = "";
    std::string new_addr = board_items[row].addr_.toStdString();
    if (origin_addr.compare(new_addr) != 0) {
      dirty_ = true;
    }
  }
}
