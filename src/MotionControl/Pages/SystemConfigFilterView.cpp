// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SystemConfigFilterView.h"

#include "../Database/PlasmaCutTechnology/PlasmaCutDataHandler.h"

SystemConfigFilterView::SystemConfigFilterView(QWidget *parent)
    : QWidget(parent) {

  view_layout_ = new QVBoxLayout(this);
  vendor_layout_ = new QHBoxLayout();
  keyword_layout_ = new QHBoxLayout();

  view_layout_->addLayout(vendor_layout_);
  view_layout_->addLayout(keyword_layout_);
  view_layout_->addStretch();
  setLayout(view_layout_);

  initialVendor();
  arrangeKeywordFilter();
}

SystemConfigFilterView::~SystemConfigFilterView() {}

void SystemConfigFilterView::onSelectVendor(int vendor_id) {
}

void SystemConfigFilterView::initialVendor() {
  vendor_ = new QComboBox(this);

  PlasmaCutDataHandler *db_handler = PlasmaCutDataHandler::GetInstance();
  std::vector<std::string> vendor_name = db_handler->GetVendorNames();
  for (size_t i = 0; i < vendor_name.size(); i++) {
    vendor_->addItem(vendor_name[i].c_str());
  }
  vendor_layout_->addWidget(vendor_);
  vendor_layout_->addStretch();

  connect(vendor_, SIGNAL(currentIndexChanged(int)), this,
      SLOT(onSelectVendor(int)));

}

void SystemConfigFilterView::arrangeKeywordFilter() {
  keyword_filter_.clear();

  PlasmaCutDataHandler *db_handler = PlasmaCutDataHandler::GetInstance();
  std::map<std::string, std::string> field = db_handler->GetSystemConfigKeywordField();
  std::map<std::string, std::string>::const_iterator iter = field.begin();
  for (; iter != field.end(); iter++) {
    keyword_filter_.push_back(new QComboBox(this));

    std::vector<std::string> filed_items = db_handler->GetFieldValues(iter->first);
    for (size_t j = 0; j < filed_items.size(); j++) {
      keyword_filter_.back()->addItem(filed_items[j].c_str());
    }
  }

  for (size_t i = 0; i < keyword_filter_.size(); i++) {
    keyword_layout_->addWidget(keyword_filter_[i]);
  }
  keyword_layout_->addStretch();
}
