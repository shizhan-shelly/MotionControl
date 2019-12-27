// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Widgets/devicediagnose/board/BoardDiagnoseForm.h"

#include "MotionControl/Cutter.h"
#include "ui_BoardDiagnoseForm.h"

BoardDiagnoseForm::BoardDiagnoseForm(QWidget *parent)
    : widget::DeviceDiagnoseWidget(parent) {

  ui_ = new Ui::BoardDiagnoseForm();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QLineEdit { font-size: 11pt; \
                 font-family: SimSun }");

}

BoardDiagnoseForm::~BoardDiagnoseForm() {
  delete ui_;
}

void BoardDiagnoseForm::setCurrentBoard(int board_index) {
  board_index_ = board_index;
}

void BoardDiagnoseForm::Update() {
}
