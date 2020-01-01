// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PAGES_DATABASEVIEW_CODETRANSFORM_CODETRANSFORMWIDGET_H__
#define PAGES_DATABASEVIEW_CODETRANSFORM_CODETRANSFORMWIDGET_H__

#include <QtGui/QWidget>

namespace Ui {
class CodeTransformWidget;
}

class CodeTransformModel;

class CodeTransformWidget : public QWidget {
  Q_OBJECT

 public:
  explicit CodeTransformWidget(QWidget *parent = NULL);
  virtual ~CodeTransformWidget();

 public slots:
  /// Insert new data item before the selected row.
  void insert();

  /// Remove the data item of the selected row.
  void remove();

 private:
  CodeTransformModel *model_;
  Ui::CodeTransformWidget *ui_;

  void initialWidget();

}; // class CodeTransformWidget

#endif // PAGES_DATABASEVIEW_CODETRANSFORM_CODETRANSFORMWIDGET_H__
