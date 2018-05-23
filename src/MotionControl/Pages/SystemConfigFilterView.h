// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef SYSTEMCONFIGFILTERVIEW_H
#define SYSTEMCONFIGFILTERVIEW_H

#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

#include "../Database/PlasmaCutTechnology/SystemConfigDefine.h"
#include "../../Widget/customwidget/ComboEditor.h"

class SystemConfigFilterView : public QWidget {
  Q_OBJECT

 public:
  explicit SystemConfigFilterView(QWidget *parent = NULL);
  ~SystemConfigFilterView();

 signals:
  void systemConfigRecord(const std::vector<std::vector<std::pair<std::string, std::string> > > &records);

 private slots:
  void onSelectVendor(const QString &vendor_name);

  void onSelectKeywordFilter(const QString &keyword_value);

 private:
  void initialVendor();

  void arrangeKeywordFilter();

  void executeKeywordFilter();

  int vendor_id_;
  QGridLayout *keyword_layout_;
  QHBoxLayout *vendor_layout_;
  QVBoxLayout *view_layout_;
  std::vector<widget::ComboEditor *> keyword_filter_;
  widget::ComboEditor *vendor_;

}; // class SystemConfigFilterView

#endif // SYSTEMCONFIGFILTERVIEW_H
