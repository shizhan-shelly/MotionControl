// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef TABLEMODELVIEW_DATAVIEW_COMBOBOXDELEGATE_H__
#define TABLEMODELVIEW_DATAVIEW_COMBOBOXDELEGATE_H__

#include <QtGui/QItemDelegate>

namespace widget {

class ComboBoxDelegate : public QItemDelegate {
 public:
  explicit ComboBoxDelegate(QObject *parent = NULL);
  virtual ~ComboBoxDelegate();

  void initialDelegate(const QStringList &list);

  virtual QWidget *createEditor(QWidget *parent,
      const QStyleOptionViewItem &option,
      const  QModelIndex &index) const;

  virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;

  virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
      const QModelIndex &index) const;

  virtual void updateEditorGeometry(QWidget *editor,
      const QStyleOptionViewItem &option, const QModelIndex &index) const;

 private:
  QList<QString> list_;

}; // class ComboBoxDelegate

} // namespace widget

#endif // TABLEMODELVIEW_DATAVIEW_COMBOBOXDELEGATE_H__
