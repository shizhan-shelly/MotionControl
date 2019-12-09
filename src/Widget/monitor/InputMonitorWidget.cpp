// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "InputMonitorWidget.h"

static const QString OPEN_ICON = ":/Widget/resource/open.png";
static const QString CLOSE_ICON = ":/Widget/resource/closed.png"

InputMonitorWidget::InputMonitorWidget(QWidget *parent)
    : QWidget(parent) {

}

InputMonitorWidget::~InputMonitorWidget() {
}

void InputMonitorWidget::Update(const std::vector<unsigned char> &input) {
  bool status[][8] = {false};
  for (size_t i = 0; i < input.size(); i++) {
    for (size_t j = 0; j < 8; j++) {
      status[i][j] = input[i] & (0x01 << j);
    }
  }
  //ui_->input1_bit0_->setPixmap(status[0][0] ? QPixmap(OPEN_ICON) : QPixmap(CLOSE_ICON));
}

void InputMonitorWidget::SetupPanel(const QVector<QVector<QString> > &infor) {
}
