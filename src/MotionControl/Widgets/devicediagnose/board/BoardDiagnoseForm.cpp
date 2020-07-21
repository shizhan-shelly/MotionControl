// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Widgets/devicediagnose/board/BoardDiagnoseForm.h"

#include "MotionControl/Controller/board/AbstractBoard.h"
#include "MotionControl/Controller/board/IOBoardManager.h"
#include "MotionControl/Cutter.h"
#include "ui_BoardDiagnoseForm.h"
//#include "device/api/BoardAPI.h"
//#include "nmlclient/NmlClient.h"

BoardDiagnoseForm::BoardDiagnoseForm(QWidget *parent)
    : widget::DeviceDiagnoseWidget(parent) {

  ui_ = new Ui::BoardDiagnoseForm();
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QLineEdit { font-size: 11pt; \
                 font-family: SimSun }");

  connect(ui_->output_port_, SIGNAL(stateChanged(int, bool)),
          this, SLOT(onOutputControl(int, bool)));

  connect(ui_->da_port_, SIGNAL(control(int, float)),
          this, SLOT(onDAControl(int, float)));

}

BoardDiagnoseForm::~BoardDiagnoseForm() {
  delete ui_;
}

void BoardDiagnoseForm::setCurrentBoard(int board_index) {
  board_index_ = board_index;
  std::map<int, AbstractBoard *> boards = IOBoardManager::GetInstance()->GetBoard();
  std::map<int, AbstractBoard *>::iterator it = boards.find(board_index_);
  AbstractBoard *board = it != boards.end() ? it->second : NULL;
  if (board) {
    int in_size = board->GetBoardInputSize();
    int out_size = board->GetBoardOutputSize();
    int ad_size = board->GetBoardADSize();
    int da_size = board->GetBoardDASize();
    std::vector<QString> input;
    for (int i = 0; i < in_size; i++) {
      ConfigItem item;
      board->GetPhyInput(i + 1, item);
      input.push_back(item.name);
    }
    std::vector<QString> output;
    for (int i = 0; i < out_size; i++) {
      ConfigItem item;
      board->GetPhyOutput(i + 1, item);
      output.push_back(item.name);
    }
    std::vector<QString> ad;
    for (int i = 0; i < ad_size; i++) {
      ADItem item;
      board->GetPhyAD(i + 1, item);
      ad.push_back(item.name);
    }
    std::vector<QString> da;
    for (int i = 0; i < da_size; i++) {
      DAItem item;
      board->GetPhyDA(i + 1, item);
      da.push_back(item.name);
    }
    QVector<QVector<QString> > display_input;
    display_input << QVector<QString>::fromStdVector(std::vector<QString>(input.begin(), input.begin() + in_size / 2));
    display_input << QVector<QString>::fromStdVector(std::vector<QString>(input.begin() + in_size / 2, input.end()));
    QVector<QVector<QString> > display_output;
    display_output << QVector<QString>::fromStdVector(std::vector<QString>(output.begin(), output.begin() + out_size / 2));
    display_output << QVector<QString>::fromStdVector(std::vector<QString>(output.begin() + out_size / 2, output.end()));
    QVector<QString> display_ad = QVector<QString>::fromStdVector(ad);
    QVector<QString> display_da = QVector<QString>::fromStdVector(da);
    ui_->input_port_->setupPanel(display_input);
    ui_->output_port_->setupPanel(display_output);
    ui_->ad_port_->setupPanel(display_ad);
    ui_->da_port_->setupPanel(display_da);

    ui_->input_port_->SetClickable(false);
  }
}

void BoardDiagnoseForm::Update() {
  if (OCutter::GetInstance()->GetController()->dev_comm_->status_ == NULL) {
    return;
  }
  Status_Board status_board = OCutter::GetInstance()->GetController()->
      dev_comm_->status_->boards_[board_index_];

  std::vector<unsigned char> input = std::vector<unsigned char>(
      status_board.input_.status_, status_board.input_.status_ +
      sizeof(status_board.input_.status_) / sizeof(unsigned char));

  std::vector<unsigned char> output = std::vector<unsigned char>(
      status_board.output_.status_, status_board.output_.status_ +
      sizeof(status_board.output_.status_) / sizeof(unsigned char));

  std::vector<double> ad = std::vector<double>(
      status_board.ad_.status_, status_board.ad_.status_ +
      sizeof(status_board.ad_.status_) / sizeof(float));

  std::vector<double> da = std::vector<double>(
      status_board.da_.status_, status_board.da_.status_ +
      sizeof(status_board.da_.status_) / sizeof(float));

  QVector<unsigned char> input_status = QVector<unsigned char>::fromStdVector(input);
  QVector<unsigned char> output_status = QVector<unsigned char>::fromStdVector(output);
  QVector<double> ad_status = QVector<double>::fromStdVector(ad);
  QVector<double> da_status = QVector<double>::fromStdVector(da);
  ui_->input_port_->Update(input_status);
  ui_->output_port_->Update(output_status);
  ui_->ad_port_->Update(ad_status);
  ui_->da_port_->Update(da_status);
}

void BoardDiagnoseForm::onOutputControl(int current_id, bool on) {
  int port_number = current_id + 1;
  BoardSetOutput(board_index_, port_number, on);
}

void BoardDiagnoseForm::onDAControl(int current_id, float value) {
  int port_number = current_id + 1;
  BoardSetDA(board_index_, port_number, value);
}
