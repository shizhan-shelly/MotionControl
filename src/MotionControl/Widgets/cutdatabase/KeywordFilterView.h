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

  void keywordFilter(const std::vector<std::pair<std::string, std::string> > &records);

 private slots:
  // index, keyword filter's sequence index.
  void onSelectKeywordFilter(int index);

 private:
  void arrangeKeywordFilter();

  void updateKeywordFilter(int index);

  QGridLayout *keyword_layout_;
  QVBoxLayout *view_layout_;
  QVector<widget::ComboEditor *> keyword_filter_;

}; // class KeywordFilterView

#endif // CUTDATABASE_KEYWORDFILTERVIEW_H__
