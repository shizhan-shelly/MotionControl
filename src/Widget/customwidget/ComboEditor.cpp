// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../customwidget/ComboEditor.h"

#include <assert.h>

#include <QtGui/QCombobox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>

namespace widget {

ComboEditor::ComboEditor(QWidget *parent) : BaseWidget(parent)
                                          , item_index_(0) {

  layout_ = new QHBoxLayout(this);
  layout_->setContentsMargins(0, 0, 0, 0);
  setLayout(layout_);
}

ComboEditor::~ComboEditor() {}

QString ComboEditor::currentEditorValue() const {
  return combobox_->currentText();
}

void ComboEditor::setupWidget(const QPair<int, QString> &infor) {
  assert(!infor.second.isEmpty());
  clearItems();
  item_index_ = infor.first;
  title_ = new QLabel(infor.second, this);
  combobox_ = new QComboBox(this);
  arrangeItems();
  connect(combobox_, SIGNAL(currentIndexChanged(QString)),
      this, SLOT(onSelectChanged(QString)));

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

void ComboEditor::setEditorValues(const QList<QString> &value) {
  if (combobox_) {
    combobox_->clear();
    combobox_->addItems(value);
  }
}

void ComboEditor::setCurrentIndex(int index) {
  if (combobox_) {
    combobox_->setCurrentIndex(index);
  }
}

void ComboEditor::onSelectChanged(const QString &text) {
  emit currentSelect(text);
  emit itemChanged(item_index_);
}

} // namespace widget
