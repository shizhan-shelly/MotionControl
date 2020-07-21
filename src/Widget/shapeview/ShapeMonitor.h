// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_SHAPEMONITOR_H__
#define CHARGEWIDGET_SHAPEMONITOR_H__

#include <QtCore/QPair>
#include <QtCore/QPointF>
#include <QtCore/QVector>
#include <QtGui/QColor>
#include <QtGui/QWidget>

class AuxiliaryWidget;
class CircleItem;
class OutLineItem;
class QGraphicsItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QMouseEvent;
class QStackedLayout;
class ShapeView;

/**
 * ShapeMonitor class is designed for displaying two widgets in the way of
 * stack access. With the help of ShapeView and AuxiliaryWidget, the
 * ShapeMonitor widget can show a real-time picture of displaying cursor's
 * track and painting solid circles, at the same time, can also view an
 * editable shape group which is made up of circles and polygons.
 * Note: Before initial the contents on the ShapeMonitor widget, please define
 * its size and show it on the screen device firstly.
 */
class ShapeMonitor : public QWidget {
  Q_OBJECT

 public:
  explicit ShapeMonitor(QWidget *parent = NULL);
  ~ShapeMonitor();

  /**
   * FunctionName: initialWidget()
   * Description:
   * Before calling this function, please make sure of showing ShapeMonitor
   * Widget on the screen device.
   * This function initializes the items on the view to be shown: an external
   * polygon shape, several internal polygons and several circles. After that,
   * the view will be displayed with the scale of 1:1.
   * @param [in]: ext_points, points on the external outline. Unit: (mm, mm).
   * @param [in]: in_points, points on the internal polygons. Unit: (mm, mm).
   * @param [in]: circles, information of circles to be shown on the view.
   * Unit: point: (mm, mm), radius: mm.
   */
  void initialWidget(const QVector<QPointF> &ext_points,
                     const QVector<QVector<QPointF> > &in_points,
                     const QVector<QPair<QPointF, double> > &circles);

  /**
   * FunctionName: setEditable()
   * Description:
   * This function will set whether the ShapeMonitor widget can move the circle
   * items.
   * @param [in]: enable, if the value is ture, circle can be moved.
   */
  void setEditable(bool enable);

  /**
   * FunctionName: setColor()
   * Description:
   * After initial the widget's contents or add new ciecles, you must call this
   * function to set the color of line and circle.
   * @param [in]: line_color, polygonline's color.
   * @param [in]: circle_color, circle's color.
   */
  void setColor(const QColor &line_color, const QColor &circle_color);

  /**
   * FunctionName: isCollided()
   * Description:
   * This function judges whether any shape item collides with the others.
   * @return: If there is one item which collides with any other items, return
   * true. Otherwise, return false.
   */
  bool isCollided();

  /**
   * FunctionName: getCircles()
   * Description:
   * This function can get new position information of circles after editing.
   * These circles to be obtained are sorted in a sequence of shortest path
   * between any two circles. The symbol information of each circle is its
   * physical position.
   * @param [in]: circle_infos, physical position of all circles.
   * Unit: (mm, mm).
   */
  void getCircles(QVector<QPointF> &circle_infos) const;

  /**
   * FunctionName: addCircle()
   * Description:
   * This function adds new circle with specifical position and radius.
   * @param [in]: pos, new circle's position.
   * @param [in]: radius, new circle's radius.
   */
  void addCircle(const QPointF &pos, double radius);

  /**
   * FunctionName: deleteCircle()
   * Description:
   * This function deletes a circle with specifical position.
   * @param [in]: pos, the position of circle to be deleted.
   */
  void deleteCircle(const QPointF &pos);

 signals:
  /**
   * FunctionName: currentPosition()
   * Description:
   * When the mouse move on the screen, this widget will emit this signal to
   * notify outside where the current position is.
   * @param [in]: pos, Unit: (mm, mm).
   */
  void currentPosition(const QPointF &pos);

 public slots:
  /**
   * FunctionName: onLocated()
   * Description:
   * This widget forwards a signal to the AuxiliaryWidget to show a cursor.
   * @param [in]: pos, Unit: (mm, mm).
   */
  void onLocated(const QPointF &pos);

  /**
   * FunctionName: onPunched()
   * Description:
   * This widget forwards a signal to the AuxiliaryWidget to show the punched
   * circles.
   * @param [in]: pos, the position of punched circle: (mm, mm).
   * @param [in]: radius, the radius of punched circle: mm.
   */
  void onPunched(const QPointF &pos, double radius);

  /**
   * FunctionName: onZoom()
   * Description:
   * This widget will zoom the view and child widget with the scale.
   * @param [in]: scale, the scale of zooming all widget.
   */
  void onZoom(double scale);

  /**
   * FunctionName: onTranslate()
   * Description:
   * This function will move this widget specific pixels on one direction.
   * @param [in]: delt_x, distance to be moved on x coordinates. Unit: pixel.
   * @param [in]: delt_y, distance to be moved on y coordinates. Unit: pixel.
   */
  void onTranslate(double delt_x, double delt_y);

  /**
   * FunctionName: onDeleted()
   * Description:
   * This function will remove the selected circle's items. When click delete
   * button, it will call this function.
   */
  void onDeleted();

 protected:
  void mouseMoveEvent(QMouseEvent *event);

 private:
  AuxiliaryWidget *monitor_widget_;
  double scale_;
  QGraphicsScene *scene_;
  QPointF cursor_point_;
  QStackedLayout *stacked_layout_;
  QVector<CircleItem *> circles_;
  QVector<OutLineItem *> outlines_;
  QVector<QGraphicsLineItem *> polygon_lines_;
  QVector<QPair<QPointF, double> > punched_circles_;
  ShapeView *shape_view_;

  /// This function initializes the external outline.
  void setExtOutLine(const QVector<QPointF> &points);

  /// This function initializes the internal polygons.
  void setInternalLine(const QVector<QVector<QPointF> > &points);

  /// This function initializes the circle to be shown on this view.
  void setCircles(const QVector<QPair<QPointF, double> > &circles);

  /// This function must be called after add all the items into the scene.
  /// Automatically adjust the widget to display all shape items and set
  /// current displaying scale as 1.
  void autoFitInWidget();

  void clearAll();

  void displayPunchedCircles();

  /// This function will calculate the most accurate position for emiting
  /// currentPostion(QPointF) signal.
  QPoint AccuratePosition(const QPoint &orig_pos);

  QPoint CalculateNearestPoint(const QPoint &point,
                               const QList<QGraphicsItem *> &item_list);

  bool isLineItems(const QList<QGraphicsItem *> &item_list);

};

#endif // CHARGEWIDGET_SHAPEMONITOR_H__
