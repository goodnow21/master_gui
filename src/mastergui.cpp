#include "mastergui.h"
#include "ui_mastergui.h"

#include <QtMultimedia/QMediaService>
#include <QtMultimedia/QMediaRecorder>
#include <QtMultimediaWidgets/QCameraViewfinder>
#include <QtMultimedia/QCameraInfo>
#include <QtMultimedia/QMediaMetaData>

#include <QMessageBox>
#include <QPalette>

MasterGui::MasterGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MasterGui)
{
  ui->setupUi(this);
  nh_.reset(new ros::NodeHandle("~"));
  ros_timer = new QTimer(this);
  connect(ros_timer, SIGNAL(timeout()), this, SLOT(spinOnce()));
  ros_timer->start(100);

  std::string hello_topic;
  nh_->param<std::string>("hello_topic",hello_topic,"chatter");
  hello_pub_ = nh_->advertise<std_msgs::String>(hello_topic,1);
}

MasterGui::~MasterGui()
{
    delete ui;
}

void MasterGui::spinOnce(){
  if(ros::ok()){
    ros::spinOnce();
  }
  else
      QApplication::quit();
}

void MasterGui::on_hiButton_clicked()
{
  std_msgs::String msg;
  std::stringstream ss;
  ss << "hello world ";
  msg.data = ss.str();

  hello_pub_.publish(msg);

}

void MasterGui::on_noseRadioButton_clicked()
{
    // forbid tool button
    ui->ultraRadioButton->setEnabled(false);
    ui->ultraRadioButton->setCheckable(false);
    // enable tool button
    ui->suctionRadioButton->setEnabled(true);
    ui->suctionRadioButton->setCheckable(true);
    ui->swabRadioButton->setEnabled(true);
    ui->swabRadioButton->setCheckable(true);
    ui->forcepRadioButton->setEnabled(true);
    ui->forcepRadioButton->setCheckable(true);
    // enable direction
    ui->leftRadioButton->setEnabled(true);
    ui->rightRadioButton->setEnabled(true);
    // enable control button
    if(ui->swabRadioButton->isChecked()==true) {
        ui->controlButton->setEnabled(true);
        ui->testButton->setEnabled(true);
        ui->nextButton->setEnabled(true);
        ui->endButton->setEnabled(true);
    } else {
        ui->controlButton->setEnabled(false);
        ui->testButton->setEnabled(false);
        ui->nextButton->setEnabled(false);
        ui->endButton->setEnabled(false);
    }
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::on_mouthRadioButton_clicked()
{
    // forbid tool button
    ui->forcepRadioButton->setEnabled(false);
    ui->forcepRadioButton->setCheckable(false);
    ui->ultraRadioButton->setEnabled(false);
    ui->ultraRadioButton->setCheckable(false);
    // enable tool button
    ui->suctionRadioButton->setEnabled(true);
    ui->suctionRadioButton->setCheckable(true);
    ui->swabRadioButton->setEnabled(true);
    ui->swabRadioButton->setCheckable(true);
    // forbid direction
    ui->leftRadioButton->setEnabled(false);
    ui->rightRadioButton->setEnabled(false);
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::on_earRadioButton_clicked()
{
    // forbid tool button
    ui->swabRadioButton->setEnabled(false);
    ui->swabRadioButton->setCheckable(false);
    ui->ultraRadioButton->setEnabled(false);
    ui->ultraRadioButton->setCheckable(false);
    // enable tool button
    ui->suctionRadioButton->setEnabled(true);
    ui->suctionRadioButton->setCheckable(true);
    ui->forcepRadioButton->setEnabled(true);
    ui->forcepRadioButton->setCheckable(true);
    // enable direction
    ui->leftRadioButton->setEnabled(true);
    ui->rightRadioButton->setEnabled(true);
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::on_neckRadioButton_clicked()
{
    // forbid tool button
    ui->suctionRadioButton->setEnabled(false);
    ui->suctionRadioButton->setCheckable(false);
    ui->swabRadioButton->setEnabled(false);
    ui->swabRadioButton->setCheckable(false);
    ui->forcepRadioButton->setEnabled(false);
    ui->forcepRadioButton->setCheckable(false);
    // enable tool button
    ui->ultraRadioButton->setEnabled(true);
    ui->ultraRadioButton->setCheckable(true);
    ui->ultraRadioButton->setChecked(true);
    // forbid direction
    ui->leftRadioButton->setEnabled(false);
    ui->rightRadioButton->setEnabled(false);
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::on_suctionRadioButton_clicked()
{
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::on_swabRadioButton_clicked()
{
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::on_forcepRadioButton_clicked()
{
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::on_ultraRadioButton_clicked()
{
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::on_leftRadioButton_clicked()
{
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::on_rightRadioButton_clicked()
{
    // check all buttons checked
    check_allButtons_checked();
}

void MasterGui::check_allButtons_checked()
{
    bool is_checked = false;
    // check
    if(ui->noseRadioButton->isChecked()==true) {
        if(ui->suctionRadioButton->isChecked()==true||ui->swabRadioButton->isChecked()==true||ui->forcepRadioButton->isChecked()==true) {
            if(ui->leftRadioButton->isChecked()==true||ui->rightRadioButton->isChecked()==true) {
                is_checked = true;
            }
        }
    } else if (ui->mouthRadioButton->isChecked()==true) {
        if(ui->suctionRadioButton->isChecked()==true||ui->swabRadioButton->isChecked()==true) {
            is_checked = true;
        }
    } else if (ui->earRadioButton->isChecked()==true) {
        if(ui->suctionRadioButton->isChecked()==true||ui->forcepRadioButton->isChecked()==true) {
            if(ui->leftRadioButton->isChecked()==true||ui->rightRadioButton->isChecked()==true) {
                is_checked = true;
            }
        }
    } else if (ui->neckRadioButton->isChecked()==true) {
        is_checked = true;
    }

    // active/deactive button
    if (is_checked==true) {
        ui->controlButton->setEnabled(true);
        ui->testButton->setEnabled(true);
        ui->nextButton->setEnabled(true);
        ui->endButton->setEnabled(true);
    } else {
        ui->controlButton->setEnabled(false);
        ui->testButton->setEnabled(false);
        ui->nextButton->setEnabled(false);
        ui->endButton->setEnabled(false);
    }

}
