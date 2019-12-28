// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Widgets/devicediagnose/board/BoardDiagnoseWidget.h"

#include "MotionControl/Cutter.h"
#include "ui_BoardDiagnoseWidget.h"

BoardDiagnoseWidget::BoardDiagnoseWidget(QWidget *parent)
    : widget::DeviceDiagnoseWidget(parent) {

  ui_ = new Ui::BoardDiagnoseWidget();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt; font-family: SimSun } \
                 QTabWidget::pane {border: none; \
                                   background: transparent;} \
                 QTabBar::tab {min-width: 70px; \
                               min-height: 40px;} \
                 QTabBar::tab:selected {color: rgb(85, 170, 255);} \
                 QTabBar::tab:!selected {color: black;}");

  connect(ui_->tab_bar_, SIGNAL(currentChanged(int)), this, SLOT(onSwitchBoard(int)));
}

BoardDiagnoseWidget::~BoardDiagnoseWidget() {
  delete ui_;
}

void BoardDiagnoseWidget::Update() {
  if (board_index_ == 0) {
    ui_->local_->Update();
  }
}

void BoardDiagnoseWidget::onSwitchBoard(int board_index) {
  board_index_ = board_index;
  if (board_index_ == 0) {
    ui_->board_stack_->setCurrentWidget(ui_->local_);
    ui_->local_->setCurrentBoard(0);
  } else if (board_index_ > 0) {
    Cutter *cutter = Cutter::GetInstance();
    QVector<BoardItem> ext_board =
        cutter->GetExtendedBoardModel()->GetExtendedBoard();

    BoardItem current_board = ext_board[board_index_ - 1];
    QString board_model = current_board.model_;
  }
}

void BoardDiagnoseWidget::showEvent(QShowEvent *event) {
  QMap<int, QString> board_infor;
  board_infor.insert(0, "Local_Board");
  Cutter *cutter = Cutter::GetInstance();
  QVector<BoardItem> ext = cutter->GetExtendedBoardModel()->GetExtendedBoard();
  foreach(BoardItem board, ext) {
    board_infor.insert(board.group_, board.model_);
  }
  ui_->tab_bar_->initBar(board_infor);
  ui_->tab_bar_->setCurrentIndex(0);
  QWidget::showEvent(event);
}
