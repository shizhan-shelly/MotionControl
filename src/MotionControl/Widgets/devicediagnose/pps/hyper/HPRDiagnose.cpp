#include "HPRDiagnose.h"

#include "ui_HPRDiagnose.h"

HPRDiagnose::HPRDiagnose(QWidget *parent)
    : QWidget(parent) {

  ui_ = new Ui::HPRDiagnose();
  ui_->setupUi(this);
}

HPRDiagnose::~HPRDiagnose() {
  delete ui_;
}

