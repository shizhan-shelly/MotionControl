// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../customwidget/ComboEditor.h"

#include <assert.h>

#include <QtGui/QCombobox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>

namespace widget {

ComboEditor::ComboEditor(QWidget *parent) : BaseWidget(parent) {
  layout_ = new QHBoxLayout(this);
  layout_->setContentsMargins(0, 0, 0, 0);
  setLayout(layout_);
}

ComboEditor::~ComboEditor() {}

void ComboEditor::setupWidget(const QPair<QString, QList<QString> > &infor) {
  assert(!infor.first.isEmpty());
  clearItems();
  title_ = new QLabel(infor.first, this);
  combobox_ = new QComboBox(this);
  combobox_->addItems(infor.second);
  arrangeItems();
}

void ComboEditor::clearItems() {
  QLayoutItem *item_widget = NULL;
  for (int i = 0; i < layout_->count(); i++) {
    item_widget = layout_->itemAt(i);
    if (item_widget) {
      item_widget->widget()->hide();
      layout_->removeItem(item_widget);
      delete item_widget;
      item_widget = NULL;
    }
  }
}

void ComboEditor::arrangeItems() {
  title_->setMinimumSize(120, 20);
  title_->setMaximumSize(120, 20);
  combobox_->setMinimumSize(120, 20);
  combobox_->setMaximumSize(120, 20);
  layout_->addWidget(title_, 1);
  layout_->addWidget(combobox_, 1);
  layout_->addSpacerItem(new QSpacerItem(100, 20,
      QSizePolicy::Expanding, QSizePolicy::Expanding));

}

} // namespace widget
