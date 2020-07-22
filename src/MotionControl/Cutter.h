// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_H__
#define CUTTER_H__

#include <QtGui/QApplication>

#include "base/singleton/Singleton.h"
#include "MotionControl/Communication/Modbus/ClientHandlerManager.h"
#include "MotionControl/controller/pps/PPSClient.h"
#include "MotionControl/Widgets/codetransform/CodeTransformModel.h"
#include "MotionControl/Widgets/extendedio/ExtendedBoardModel.h"
#include "MotionControl/Widgets/kerftable/KerfTableModel.h"

class Cutter : public Singleton {
  DECLARE_SINGLETON(Cutter)

 public:
  QString LocalBoardModel() const;
  QString ConfigDirPath() const;

  void InitPPSClient();

  bool StartupPPSConnect();

  PPSClient *pps_client() {
    return &pps_client_;
  }

  ExtendedBoardModel *GetExtendedBoardModel() {
    return &extended_board_model_;
  }

  KerfTableModel *GetKerfTableModel() {
    return &kerf_table_model_;
  }

  CodeTransformModel *GetCodeTransformModel() {
    return &code_transform_model_;
  }

  void InitKerfTableModel();

  void InitExtendedBoardModel();

 private:
  Cutter();
  ~Cutter();

  PPSClient pps_client_;
  ClientHandlerManager client_manager_;
  CodeTransformModel code_transform_model_;
  ExtendedBoardModel extended_board_model_;
  KerfTableModel kerf_table_model_;

}; //class Cutter

#endif // CUTTER_H__
