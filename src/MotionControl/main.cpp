// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include <QtCore/QSharedMemory>
#include <QtGui/QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  /// Ensure the program only has one instance.
  QSharedMemory run_one_instance("www.zhanshi-welcome.com");
  if (!run_one_instance.create(1)) {
    return -1;
  }

  return app.exec();
}
