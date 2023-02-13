#include "mastergui.h"
#include "ui_mastergui.h"

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
