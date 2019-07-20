// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGETS_EXTENDEDIO_EXTENDEDBOARDMODEL_H__
#define WIDGETS_EXTENDEDIO_EXTENDEDBOARDMODEL_H__

#include <QtCore/QAbstractTableModel>
#include <QtCore/QVector>

#include "MotionControl/Controller/DeviceDefine.h"

class ExtendedBoardModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit ExtendedBoardModel(QObject *parent = NULL);
  ~ExtendedBoardModel();

  void initialExtendedBoard(const QVector<BoardItem> &initial);

  QVector<BoardItem> GetExtendedBoard() const;

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  // The dataChanged() signal should be emitted if the data was successfully set.
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

 private:
  QVector<BoardItem> board_items_;

}; // class ExtendedBoardModel

#endif // WIDGETS_EXTENDEDIO_EXTENDEDBOARDMODEL_H__
