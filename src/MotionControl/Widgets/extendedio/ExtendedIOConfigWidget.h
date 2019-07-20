// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGETS_EXTENDEDIO_EXTENDEDIOCONFIGWIDGET_H__
#define WIDGETS_EXTENDEDIO_EXTENDEDIOCONFIGWIDGET_H__

#include <QtCore/QModelIndex>
#include <QtGui/QWidget>

namespace Ui {
class ExtendedIOConfigWidget;
}

namespace widget {
class ComboBoxDelegate;
}

class ExtendedBoardModel;

class ExtendedIOConfigWidget : public QWidget {
  Q_OBJECT

 public:
  explicit ExtendedIOConfigWidget(QWidget *parent = NULL);
  virtual ~ExtendedIOConfigWidget();

  bool isDirty();

  bool isValid();

  void commit();

  void revert();

 private slots:
  void onDataChanged(const QModelIndex &topLeft,
                     const QModelIndex &bottomRight);

 private:
  bool dirty_;
  ExtendedBoardModel *extended_board_model_;
  Ui::ExtendedIOConfigWidget *ui_;
  widget::ComboBoxDelegate *model_delegate_;

  void initialConfigWidget();
  void resetExtendedBoardModel();

}; // class ExtendedIOConfigWidget

#endif // WIDGETS_EXTENDEDIO_EXTENDEDIOCONFIGWIDGET_H__
