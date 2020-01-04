// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Widgets/devicediagnose/board/BoardDiagnoseForm.h"

#include "MotionControl/controller/IOBoardManager.h"
#include "MotionControl/Cutter.h"
#include "ui_BoardDiagnoseForm.h"

BoardDiagnoseForm::BoardDiagnoseForm(QWidget *parent)
    : widget::DeviceDiagnoseWidget(parent) {

  ui_ = new Ui::BoardDiagnoseForm();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QLineEdit { font-size: 11pt; \
                 font-family: SimSun }");

  connect(ui_->output_port_, SIGNAL(stateChanged(int, bool)),
          this, SLOT(onOutputControl(int, bool)));

  connect(ui_->da_port_, SIGNAL(control(int, int)),
          this, SLOT(onDAControl(int, int)));

}

BoardDiagnoseForm::~BoardDiagnoseForm() {
  delete ui_;
}

void BoardDiagnoseForm::setCurrentBoard(int board_index) {
  board_index_ = board_index;
}

void BoardDiagnoseForm::Update() {
}

void BoardDiagnoseForm::onOutputControl(int current_id, bool on) {
}

void BoardDiagnoseForm::onDAControl(int current_id, int value) {
}
