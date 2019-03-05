// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTTER_WIDGET_PLASMA_NESTINGMODEL_H__
#define CUTTTER_WIDGET_PLASMA_NESTINGMODEL_H__

#include <QtCore/QAbstractTableModel>
#include <QtCore/QVector>

class NestingModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit NestingModel(QObject *parent = NULL);
  virtual ~NestingModel();

  bool initialNesting();

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  // The dataChanged() signal should be emitted if the data was successfully set.
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

 private:
  QVector<double> diameters_;
  std::map<std::string, std::string> keyword_filed_;

}; // class NestingModel

#endif // CUTTTER_WIDGET_PLASMA_NESTINGMODEL_H__
