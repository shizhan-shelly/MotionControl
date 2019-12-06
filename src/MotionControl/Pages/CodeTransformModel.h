// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_CODETRANSFORM_CODETRANSFORMMODEL_H__
#define CUTTER_WIDGET_CODETRANSFORM_CODETRANSFORMMODEL_H__

#include <QtCore/QAbstractTableModel>

namespace cutter {

class CodeTransformModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit CodeTransformModel(QObject *parent = NULL);
  virtual ~CodeTransformModel();

  bool initial();

  bool save();

  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

  bool insertRow(int row, const QModelIndex &parent = QModelIndex());

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  // The dataChanged() signal should be emitted if the data was successfully set.
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

 private:
  QList<std::map<std::string, std::string> > db_items_;

  QString GetItemValue(const QModelIndex &index) const;

  void SetItemValue(const QModelIndex &index, const QString &value);

}; // class CodeTransformModel

} // namespace cutter

#endif // CUTTER_WIDGET_CODETRANSFORM_CODETRANSFORMMODEL_H__
