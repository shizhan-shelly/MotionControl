#ifndef HPRDIAGNOSE_H
#define HPRDIAGNOSE_H

#include <QWidget>

namespace Ui {
class HPRDiagnose;
};

class HPRDiagnose : public QWidget {
  Q_OBJECT

 public:
  explicit HPRDiagnose(QWidget *parent = NULL);
  virtual ~HPRDiagnose();

 private:
  Ui::HPRDiagnose *ui_;

}; // class HPRDiagnose

#endif // HPRDIAGNOSE_H
