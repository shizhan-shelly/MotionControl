// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_PAGE_OEXTENDEDIOCONFIGWIDGET_H__
#define CUTTER_PAGE_OEXTENDEDIOCONFIGWIDGET_H__

#include <QtGui/QWidget>

namespace Ui {
class CodeTransformWidget;
}

namespace cutter {

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

} // namespace cutter

#endif // CUTTER_PAGE_OEXTENDEDIOCONFIGWIDGET_H__
