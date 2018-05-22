// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SystemConfigFilterView.h"

#include "../Database/PlasmaCutTechnology/PlasmaCutDataHandler.h"

SystemConfigFilterView::SystemConfigFilterView(QWidget *parent)
    : QWidget(parent) {

  view_layout_ = new QVBoxLayout(this);
  vendor_layout_ = new QHBoxLayout();
  keyword_layout_ = new QGridLayout();

  view_layout_->addLayout(vendor_layout_);
  view_layout_->addLayout(keyword_layout_);
  view_layout_->addStretch();
  setLayout(view_layout_);

  initialVendor();
  arrangeKeywordFilter();
}

SystemConfigFilterView::~SystemConfigFilterView() {}

void SystemConfigFilterView::onSelectVendor(const QString &vendor_name) {
  PlasmaCutDataHandler *db_handler = PlasmaCutDataHandler::GetInstance();
  vendor_id_ = db_handler->GetVendorID(vendor_name.toStdString());
  arrangeKeywordFilter();
}

void SystemConfigFilterView::initialVendor() {
  vendor_ = new widget::ComboEditor(this);

  PlasmaCutDataHandler *db_handler = PlasmaCutDataHandler::GetInstance();
  std::vector<std::string> vendor_name = db_handler->GetVendorNames();
  QStringList vendor_name_list;
  for (size_t i = 0; i < vendor_name.size(); i++) {
    vendor_name_list << vendor_name[i].c_str();
  }
  vendor_->setupWidget(QPair<QString, QList<QString> >("VENDOR", vendor_name_list));
  vendor_layout_->addWidget(vendor_);
  vendor_layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum,
      QSizePolicy::Expanding));

  connect(vendor_, SIGNAL(currentSelect(QString)), this, SLOT(onSelectVendor(QString)));
  vendor_id_ = 1;
}

void SystemConfigFilterView::arrangeKeywordFilter() {
  keyword_filter_.clear();
  QLayoutItem *item_widget = NULL;
  for (int i = 0; i < keyword_layout_->rowCount(); i++) {
    for (int j = 0; j < keyword_layout_->columnCount(); j++) {
      item_widget = keyword_layout_->itemAtPosition(i, j);
      if (item_widget) {
        item_widget->widget()->hide();
        keyword_layout_->removeItem(item_widget);
        delete item_widget;
        item_widget = NULL;
      }
    }
  }

  PlasmaCutDataHandler *db_handler = PlasmaCutDataHandler::GetInstance();
  std::vector<std::pair<std::string, std::string> > keyword_field =
      db_handler->GetSystemConfigKeywordField();

  std::vector<std::pair<std::string, std::string> >::const_iterator iter = keyword_field.begin();
  for (; iter != keyword_field.end(); iter++) {
    keyword_filter_.push_back(new widget::ComboEditor(this));

    std::vector<std::string> filed_item =
        db_handler->GetSystemConfigFieldValues(vendor_id_, iter->first);

    QStringList filed_item_list;
    for (size_t i = 0; i < filed_item.size(); i++) {
      filed_item_list << filed_item[i].c_str();
    }
    keyword_filter_.back()->setupWidget(
        QPair<QString, QList<QString> >(iter->first.c_str(), filed_item_list));

  }
  static const int MAX_COUNT_IN_ROW = 5;
  for (size_t i = 0; i < keyword_filter_.size(); i++) {
    keyword_layout_->addWidget(keyword_filter_[i], i / MAX_COUNT_IN_ROW, i % MAX_COUNT_IN_ROW);
  }
  keyword_layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding),
      keyword_filter_.size(), 0);

}
