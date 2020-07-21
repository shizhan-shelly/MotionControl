// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_AUXILIARYWIDGET_H__
#define CHARGEWIDGET_AUXILIARYWIDGET_H__

#include <QtCore/QPair>
#include <QtCore/QPointF>
#include <QtCore/QVector>
#include <QtGui/QColor>
#include <QtGui/QWidget>

/**
 * AuxiliaryWidget inherits from QWidget and is designed for showing a custom
 * cursor and some solid circles.
 */
class AuxiliaryWidget : public QWidget {
  Q_OBJECT

 public:
  explicit AuxiliaryWidget(QWidget *parent = NULL);
  ~AuxiliaryWidget();

  /**
   * FunctionName: clearAll()
   * Description:
   * This function clears all circles and paint the cursor on the original
   * position.
   */
  void clearAll();

 public slots:
  /**
   * FunctionName: onPunched()
   * Description:
   * Once outside emits punched() to this widget, this fuction will repaint
   * new circle and existed circles.
   * @param [in]: circles, all circles' positions and radius.
   */
  void onPunched(const QVector<QPair<QPointF, double> > &circles);

  /**
   * FunctionName: onLocated()
   * Description:
   * Once outside emits located() to this widget, this fuction will repaint
   * the cursor and all circles.
   * @param [in]: pos, the position of cursor.
   */
  void onLocated(const QPointF &pos);

  /**
   * FunctionName: onCloseToPoint()
   * Description:
   * When close to a specical point, draw a solid point.
   * @param [in]: point, the specical point.
   * @param [in]: update_pos, whether need to draw the point.
   */
  void onCloseToPoint(const QPoint &point, bool update_pos);

 protected:
  void paintEvent(QPaintEvent *event);

 private:
  bool update_pos_;
  QPoint accurate_position_;
  QPointF cursor_position_;
  QVector<QPair<QPointF, double> > circles_;
  static const QColor PROC_COLOR_;
  static const QColor CURSOR_COLOR_;
  static const QPointF ORIGINAL_POS_;

}; // class AuxiliaryWidget

#endif // CHARGEWIDGET_AUXILIARYWIDGET_H__
