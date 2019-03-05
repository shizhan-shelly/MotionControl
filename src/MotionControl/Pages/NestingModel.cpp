// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "NestingModel.h"

//#include "cutter/OCutter.h"

static const std::string LIST_ITEMS[] = {
  "Diameter",
  "CuttingSpeed",
  "LeadInSpeed",
  "Kerf",
  "AsynchronousStop",

};

static const int ITEMS_NUM = 5;

NestingModel::NestingModel(QObject *parent) : QAbstractTableModel(parent) {}

NestingModel::~NestingModel() {}

bool NestingModel::initialNesting() {
  //OCutter *cutter = OCutter::GetInstance();
  //keyword_filed_.clear();
  //cutter->GetCutChart()->GetCurrentSelectedRecord(keyword_filed_);
  //diameters_ = QVector::fromStdVector(
  //    cutter->GetNesting()->GetInteriorProfileDiameter(keyword_filed_));

  return !diameters_.isEmpty();
}

int NestingModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return diameters_.count();
}

int NestingModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return ITEMS_NUM;
}

Qt::ItemFlags NestingModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return Qt::ItemIsEnabled;
  }
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant NestingModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }
  int row = index.row();
  int column = index.column();
  if (row < 0 || row >= rowCount() || column < 0 || column >= columnCount()) {
    return QVariant();
  }
  //QString refer_diameter = QString("%1").arg(diameters_[row], 0, 'f', 1);
  //std::map<std::string, std::string> interior_profile_items =
  //    cutter->GetNesting()->GetInteriorProfileItemValue(refer_diameter, keyword_filed_);

  switch (role) {
   case Qt::DisplayRole:
   case Qt::EditRole:

    return QVariant();
   case Qt::BackgroundRole:
    return QVariant();
   case Qt::TextAlignmentRole:
    return QVariant(Qt::AlignCenter);
   default:
    return QVariant();
  }
}

QVariant NestingModel::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role) const {

  if (role != Qt::DisplayRole) {
    return QVariant();
  }
  if (orientation == Qt::Horizontal) {
    switch (section) {
     case 0:
     case 1:
     case 2:
     case 3:
     case 4:
      return tr(LIST_ITEMS[section].c_str());
     default:
      return QVariant();
    }
  }
  return QVariant();
}

bool NestingModel::setData(const QModelIndex &index, const QVariant &value,
    int role) {

  if (index.isValid() && role == Qt::EditRole) {
    emit dataChanged(index, index);
    return true;
  }
  return false;
}
