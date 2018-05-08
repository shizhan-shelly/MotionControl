// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SystemConfigFilterView.h"

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
}

SystemConfigFilterView::~SystemConfigFilterView() {}

void SystemConfigFilterView::onSelectVendor(int vendor_id) {
}

void SystemConfigFilterView::initialVendor() {
  vendor_ = new QComboBox(this);
  vendor_->addItem(tr("Kjellberg"));
  vendor_->addItem(tr("Hyperthem"));
  vendor_->addItem(tr("Liuhe"));

  vendor_layout_->addWidget(vendor_);
  vendor_layout_->addStretch();
  refreshKeywordFilter();
}

void SystemConfigFilterView::refreshKeywordFilter() {
  keyword_filter_.clear();
  keyword_filter_.push_back(new QComboBox(this));
  keyword_filter_.push_back(new QComboBox(this));
  keyword_filter_.push_back(new QComboBox(this));

  keyword_filter_[0]->addItem("Smart Focus 120");
  keyword_filter_[0]->addItem("Smart Focus 130");

  for (size_t i = 0; i < keyword_filter_.size(); i++) {
    keyword_layout_->addWidget(keyword_filter_[i]);
  }
  keyword_layout_->addStretch();
}
