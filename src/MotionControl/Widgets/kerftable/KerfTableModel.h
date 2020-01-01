// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef KERFTABLEMODEL_H__
#define KERFTABLEMODEL_H__

#include <QtCore/QAbstractTableModel>
#include <QtCore/QVector>

class KerfTableModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit KerfTableModel(QObject *parent = NULL);
  ~KerfTableModel();

  void initialKerfTableValue(const QVector<double> &initial);

  QVector<double> GetKerfTableValue() const;

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  // The dataChanged() signal should be emitted if the data was successfully set.
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

 private:
  QVector<double> kerf_variable_value_;

  double correctKerfValue(int index) const;

}; // class KerfTableModel

#endif // KERFTABLEMODEL_H__
