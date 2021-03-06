// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTDATABASE_KEYWORDFILTERVIEW_H__
#define CUTDATABASE_KEYWORDFILTERVIEW_H__

#include <map>
#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

#include "Widget/customwidget/ComboEditor.h"

class KeywordFilterView : public QWidget {
  Q_OBJECT

 public:
  explicit KeywordFilterView(QWidget *parent = NULL);
  ~KeywordFilterView();

  bool Delete();

 signals:
  void KeywordChanged(int index);
  void keywordFilter(const std::map<std::string, std::string> &records);

 protected:
  virtual void showEvent(QShowEvent *event);

 private slots:
  // index, keyword filter's sequence index.
  void onSelectKeywordFilter(int index);

 private:
  void arrangeKeywordFilter();

  void updateKeywordFilter(int index);

  void executeKeywordFilter();

  std::map<std::string, std::string> GetSelectedKeywords(int index) const;

  QGridLayout *keyword_layout_;
  QVBoxLayout *view_layout_;
  QVector<widget::ComboEditor *> keyword_filter_;
  std::vector<std::pair<std::string, std::string> > keyword_field_;

}; // class KeywordFilterView

#endif // CUTDATABASE_KEYWORDFILTERVIEW_H__
