// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef SYSTEMCONFIGFILTERVIEW_H
#define SYSTEMCONFIGFILTERVIEW_H

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QComboBox>

#include "../Database/PlasmaCutTechnology/SystemConfigDefine.h"

class SystemConfigFilterView : public QWidget {
  Q_OBJECT

 public:
  explicit SystemConfigFilterView(QWidget *parent = NULL);
  ~SystemConfigFilterView();

 signals:
  void filter(std::map<SystemConfigFilter, std::string> keyword);

 private slots:
  void onSelectVendor(int vendor_id);

 private:
  void initialVendor();

  void refreshKeywordFilter();

  QHBoxLayout *vendor_layout_;
  QHBoxLayout *keyword_layout_;
  QVBoxLayout *view_layout_;
  QComboBox *vendor_;
  std::vector<QComboBox *> keyword_filter_;

}; // class SystemConfigFilterView

#endif // SYSTEMCONFIGFILTERVIEW_H
