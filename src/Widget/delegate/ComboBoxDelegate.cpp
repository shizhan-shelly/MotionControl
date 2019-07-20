// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../delegate/ComboBoxDelegate.h"

#include <QtGui/QCombobox.h>

namespace widget {

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    : QItemDelegate(parent) {}

ComboBoxDelegate::~ComboBoxDelegate() {}

void ComboBoxDelegate::initialDelegate(const QStringList &list) {
  list_ = list;
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const {

  Q_UNUSED(option);
  Q_UNUSED(index);
  QComboBox *editor = new QComboBox(parent);
  editor->addItems(list_);
  editor->setCurrentIndex(0);
  return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
  QString text = index.model()->data(index, Qt::EditRole).toString();
  QComboBox *comboBox = static_cast<QComboBox *>(editor);
  if (comboBox) {
    int cur_index = comboBox->findText(text);
    comboBox->setCurrentIndex(cur_index);
  } else {
    QItemDelegate::setEditorData(editor, index);
  }
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const {

  QComboBox *comboBox = static_cast<QComboBox *>(editor);
  if (comboBox) {
    model->setData(index, comboBox->currentText(), Qt::EditRole);
  } else {
    QItemDelegate::setModelData(editor, model, index);
  }
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const {

  Q_UNUSED(index);
  editor->setGeometry(option.rect);
}

} // namespace widget
