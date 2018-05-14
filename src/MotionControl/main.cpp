// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include <QtCore/QSharedMemory>
#include <QtGui/QApplication>

#include "base/singleton/SingletonMaster.h"
#include "Pages\SystemConfigModel.h"
#include "Pages\SystemConfigWidget.h"
#include "Database\PlasmaCutTechnology\PlasmaCutDataHandler.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  /// Ensure the program only has one instance.
  QSharedMemory run_one_instance("www.zhanshi-welcome.com");
  if (!run_one_instance.create(1)) {
    return -1;
  }
  SingletonMaster::Activate();

  PlasmaCutDataHandler *db_handler = PlasmaCutDataHandler::GetInstance();
  if (db_handler->InitialDatabaseAccess("E:\\MyJob\\MotionControl\\tools\\test.db", "123456")) {
    std::vector<std::map<SystemConfigFilter, std::string> > items = db_handler->GetSystemConfigItems(1);
    for (size_t i = 0; i < items.size(); i++) {
      printf("%s\n", items[i][PlasmaPowerModel].c_str());
      printf("%s\n", items[i][GasBoxModel].c_str());
      printf("%s\n", items[i][TorchModel].c_str());
      printf("%s\n", items[i][Version].c_str());
    }
  }
  SystemConfigWidget widget;
  SystemConfigModel model;
  widget.setModel(&model);
  widget.show();

  return app.exec();
}
