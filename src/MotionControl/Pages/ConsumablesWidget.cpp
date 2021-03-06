// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../Pages/ConsumablesWidget.h"

#include "../../Widget/listwidget/BaseListWidgetItem.h"
#include "ui_ConsumablesWidget.h"

static const QSize ITEM_SIZE = QSize(240, 240);

ConsumablesWidget::ConsumablesWidget(QWidget *parent)
    : ::widget::BaseWidget(parent) {

  ui_ = new Ui::ConsumablesWidgetForm;
  ui_->setupUi(this);

  ui_->list_widget_->setIconSize(ITEM_SIZE);
}

ConsumablesWidget::~ConsumablesWidget() {
  delete ui_;
}

void ConsumablesWidget::clearAll() {
  ui_->list_widget_->clear();
  icon_items_.clear();
}

void ConsumablesWidget::showConsumables(const QVector<QPair<QString, QString> > &consumables) {
  clearAll();
  for (int i = 0; i < consumables.size(); i++) {
    widget::BaseListWidgetItem *item = new widget::BaseListWidgetItem(ui_->list_widget_);
    item->setIconScaled(consumables[i].first, 400, 300);
    item->setText(consumables[i].second);
    icon_items_.push_back(item);
    ui_->list_widget_->addItem(item);
  }
}
