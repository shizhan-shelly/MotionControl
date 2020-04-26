// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTDATABASE_KEYWORDFILTERVIEW_H__
#define CUTDATABASE_KEYWORDFILTERVIEW_H__

#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

#include "Widget/customwidget/ComboEditor.h"

class KeywordFilterView : public QWidget {
  Q_OBJECT

 public:
  explicit KeywordFilterView(QWidget *parent = NULL);
  ~KeywordFilterView();

 signals:
  void currentKeyword(const std::vector<std::pair<std::string, std::string> > &records);

 private slots:
  void onSelectKeywordFilter(const QString &keyword_value);

 private:
  void arrangeKeywordFilter();

  void executeKeywordFilter();

  QGridLayout *keyword_layout_;
  QVBoxLayout *view_layout_;
  std::vector<widget::ComboEditor *> keyword_filter_;

}; // class KeywordFilterView

#endif // CUTDATABASE_KEYWORDFILTERVIEW_H__
