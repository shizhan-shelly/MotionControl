// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Cutter.h"

#include "MotionControl/Communication/Modbus/RTUClientHandler.h"

Cutter::Cutter() {}

Cutter::~Cutter() {}

QString Cutter::ConfigDirPath() const {
  return QApplication::applicationDirPath() + "//config";
}

void Cutter::InitPPSClient() {
  pps_client_.SetClientHandlerManager(&client_manager_);
}

bool Cutter::StartupPPSConnect() {
  ClientHandler *client_handler_ = new RTUClientHandler("COM1", 19200, 'E', 8, 1, 1);
  client_manager_.RegisterClientHandler(client_handler_);
  return pps_client_.SetupConnect();
}

void Cutter::InitKerfTableModel() {
  QVector<double> kerf_table_value = QVector<double>(20, 0.0);
  kerf_table_model_.initialKerfTableValue(kerf_table_value);
}

void Cutter::InitExtendedBoardModel() {
  QVector<BoardItem> board_items;
  for (int i = 1; i < BOARD_SIZE; i++) {
    BoardItem board_item;
    board_item.group_ = i;
    board_items.push_back(board_item);
  }
  extended_board_model_.initialExtendedBoard(board_items);
}
