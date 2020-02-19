// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../buttonbox/ButtonBar.h"

#include <assert.h>

#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton.h>

namespace widget {

ButtonBar::ButtonBar(QWidget *parent)
    : QWidget(parent)
    , btn_group_(NULL)
    , layout_(NULL) {

  layout_ = new QGridLayout(this);
  layout_->setMargin(0);
  layout_->setSpacing(5);
  setLayout(layout_);
  btn_group_ = new QButtonGroup(this);
  connect(btn_group_, SIGNAL(buttonClicked(int)), this, SIGNAL(ButtonChecked(int)));
}

ButtonBar::~ButtonBar() {
  removeButtons();
}

void ButtonBar::removeButtons() {
  foreach (QAbstractButton *btn, btn_group_->buttons()) {
    btn_group_->removeButton(btn);
  }
  for (int i = 0; i < layout_->rowCount(); i++) {
    for(int j = 0; j < layout_->columnCount(); j++) {
      QLayoutItem *item = layout_->itemAtPosition(i, j);
      if (item != NULL) {
        QWidget *widget = item->widget();
        if (widget) {
          widget->hide();
        }
        layout_->removeItem(item);
        delete item;
        item = NULL;
      }
    }
  }
}

void ButtonBar::initBar(const QMap<int, QString> &bar_infor) {
  assert(!bar_infor.empty());
  removeButtons();
  QMap<int, QString>::const_iterator it = bar_infor.begin();
  for (int i = 0; it != bar_infor.end(); i++) {
    for (int j = 0; j < MAX_BTN_CNT && it != bar_infor.end(); j++) {
      QPushButton *btn = new QPushButton();
      btn->setMinimumSize(50, 50);
      btn->setText(it.value());
      btn_group_->addButton(btn, it.key());
      layout_->addWidget(btn, i, j);
      ++it;
    }
  }
  QSpacerItem *spacer_ = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout_->addItem(spacer_, 0, layout_->columnCount());
}

} // namespace widget
