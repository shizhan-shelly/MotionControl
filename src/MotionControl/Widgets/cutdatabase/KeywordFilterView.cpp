// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Widgets/cutdatabase/KeywordFilterView.h"

KeywordFilterView::KeywordFilterView(QWidget *parent)
    : QWidget(parent) {

  view_layout_ = new QVBoxLayout(this);
  keyword_layout_ = new QGridLayout();

  view_layout_->addLayout(keyword_layout_);
  view_layout_->addStretch();
  setLayout(view_layout_);

  arrangeKeywordFilter();
}

KeywordFilterView::~KeywordFilterView() {}

void KeywordFilterView::onSelectKeywordFilter(int index) {
  if (index == keyword_filter_.count() - 1) {
    executeKeywordFilter();
  } else {
    updateKeywordFilter(index + 1);
  }
}

void KeywordFilterView::arrangeKeywordFilter() {
  keyword_filter_.clear();
  QLayoutItem *item_widget = NULL;
  for (int i = 0; i < keyword_layout_->rowCount(); i++) {
    for (int j = 0; j < keyword_layout_->columnCount(); j++) {
      item_widget = keyword_layout_->itemAtPosition(i, j);
      if (item_widget) {
        if (item_widget->widget()) {
          item_widget->widget()->hide();
        }
        keyword_layout_->removeItem(item_widget);
        delete item_widget;
        item_widget = NULL;
      }
    }
  }

  std::vector<std::pair<std::string, std::string> > keyword_field;
  for (size_t it = 0; it < keyword_field.size(); it++) {
    keyword_filter_.push_back(new widget::ComboEditor(this));
    std::vector<std::string> filed_item;
    QStringList filed_item_list;
    for (size_t i = 0; i < filed_item.size(); i++) {
      filed_item_list << filed_item[i].c_str();
    }
    keyword_filter_.back()->setupWidget(
        QPair<QString, QList<QString> >(keyword_field[it].first.c_str(), filed_item_list));

    connect(keyword_filter_.back(), SIGNAL(currentSelect(QString)), this,
        SLOT(onSelectKeywordFilter(int)));

  }
  static const int MAX_COUNT_IN_ROW = 5;
  for (size_t i = 0; i < keyword_filter_.size(); i++) {
    keyword_layout_->addWidget(keyword_filter_[i], i / MAX_COUNT_IN_ROW, i % MAX_COUNT_IN_ROW);
  }
  keyword_layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding),
      keyword_layout_->rowCount(), 0);

}

void KeywordFilterView::updateKeywordFilter(int inddex) {
}

void KeywordFilterView::executeKeywordFilter() {
}

void KeywordFilterView::showEvent(QShowEvent *event) {
  updateKeywordFilter(0);
  QWidget::showEvent(event);
}
