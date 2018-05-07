// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef SYSTEMCONFIGTABLEVIEW_H__
#define SYSTEMCONFIGTABLEVIEW_H__

#include <QtGui/QTableView>

class SystemConfigTableView : public QTableView {
  Q_OBJECT

 public:
  explicit SystemConfigTableView(QWidget *parent = NULL);
  ~SystemConfigTableView();

}; // class SystemConfigTableView

#endif // SYSTEMCONFIGTABLEVIEW_H__
