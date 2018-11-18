// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include <QtCore/QSharedMemory>
#include <QtGui/QApplication>

#include "base/singleton/SingletonMaster.h"
#include "Cutter.h"
#include "Pages\SystemConfigModel.h"
#include "Pages\SystemConfigWidget.h"
#include "Pages\ConsumablesWidget.h"
#include "Pages/ModbusSetDlg.h"
#include "Pages/KerfTableDlg.h"
#include "Database\PlasmaCutTechnology\PlasmaCutDataHandler.h"
#include "../Widget/WidgetQrc.h"
#include "MotionControlQrc.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  /// Ensure the program only has one instance.
  QSharedMemory run_one_instance("www.zhanshi-welcome.com");
  if (!run_one_instance.create(1)) {
    return -1;
  }
  SingletonMaster::Activate();

  WidgetQrc widget_qrc;
  MotionControlQrc motion_control_qrc;

  PlasmaCutDataHandler *db_handler = PlasmaCutDataHandler::GetInstance();
  if (db_handler->InitialDatabaseAccess("E:\\MyJob\\MotionControl\\tools\\test.db", "123456")) {
    printf("Initial dabase successfully!");
  }
  SystemConfigWidget widget;
  SystemConfigModel model;
  widget.setModel(&model);
  widget.show();

  ConsumablesWidget cononsumables_widget;
  QVector<QPair<QString, QString> > info;
  info
      << QPair<QString, QString>(":/Widget/resource/edit.png", QObject::tr("Left top A"))
      << QPair<QString, QString>(":/Widget/resource/edit.png", QObject::tr("Left top B"))
      << QPair<QString, QString>(":/Widget/resource/edit.png", QObject::tr("Left top C"))
      << QPair<QString, QString>(":/Widget/resource/edit.png", QObject::tr("Left top D"))
      << QPair<QString, QString>(":/Widget/resource/edit.png", QObject::tr("Right top A"))
      << QPair<QString, QString>(":/Widget/resource/edit.png", QObject::tr("Right top B"))
      << QPair<QString, QString>(":/Widget/resource/edit.png", QObject::tr("Right top C"))
      << QPair<QString, QString>(":/Widget/resource/edit.png", QObject::tr("Right top D"));

  cononsumables_widget.showConsumables(info);
  cononsumables_widget.show();

  ModbusSetDlg thc_set_dlg;
  thc_set_dlg.SetModbusProtocol(RTU);
  thc_set_dlg.exec();

  Cutter *cutter = Cutter::GetInstance();
  cutter->InitModbusClient();
  cutter->StartupModbusConnect();

  cutter->InitKerfTableModel();
  KerfTableDlg kerf_table_dialog;
  kerf_table_dialog.setModel(cutter->GetKerfTableModel());
  kerf_table_dialog.exec();

  return app.exec();
}
