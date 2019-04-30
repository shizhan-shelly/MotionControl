// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "JobProgressDlg.h"

#include "ProgressCtrl.h"

static const int PROGRESS_CYCLE = 1000;

JobProgressDlg::JobProgressDlg(QWidget *parent) : widget::BaseDialog(parent)
                                                , entry_(0)
                                                , progress_ctrl_(NULL) {

  progress_ctrl_ = new ProgressCtrl(this);
  ui_->stack_widget_->addWidget(progress_ctrl_);
  ui_->stack_widget_->setCurrentWidget(progress_ctrl_);
  connect(&start_timer_, SIGNAL(timeout()), this, SLOT(OnTimer()));
}

JobProgressDlg::~JobProgressDlg() {
  if (progress_ctrl_) {
    delete progress_ctrl_;
  }
}

void JobProgressDlg::StartProgress() {
  //OCutter *cutter = OCutter::GetInstance();
  entry_ = 100;//cutter->GetJobManager()->PLCJobsCount();
  progress_ctrl_->initProgress(QObject::tr("Download PLC Job list. Please wait!"), entry_);
  start_timer_.start(PROGRESS_CYCLE);
}

void JobProgressDlg::OnTimer() {
  //JobManager *job_manager = OCutter::GetInstance()->GetJobManager();
  //int index = job_manager->CurDownloadJob();
  static int index = 0;
  index++;
  progress_ctrl_->onProgress(index);
  //if (job_manager->IsIdle()) {
  if (index == entry_) {
    index = 0;
    start_timer_.stop();
    close();
  }
}
