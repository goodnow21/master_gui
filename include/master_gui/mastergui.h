#ifndef MASTERGUI_H
#define MASTERGUI_H

#include <QMainWindow>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraImageCapture>
#include <QtMultimedia/QMediaRecorder>
#include <QScopedPointer>


#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>


namespace Ui {
class MasterGui;
}

class MasterGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit MasterGui(QWidget *parent = nullptr);
    ~MasterGui();

public slots:

  // ROS
  void spinOnce();

private slots:
  void on_hiButton_clicked();

  // radio button
  void on_noseRadioButton_clicked();
  void on_mouthRadioButton_clicked();
  void on_neckRadioButton_clicked();
  void on_earRadioButton_clicked();
  void on_suctionRadioButton_clicked();
  void on_swabRadioButton_clicked();
  void on_forcepRadioButton_clicked();
  void on_ultraRadioButton_clicked();
  void on_leftRadioButton_clicked();
  void on_rightRadioButton_clicked();
  void check_allButtons_checked();

private:
    Ui::MasterGui *ui;
    QTimer *ros_timer;

    ros::NodeHandlePtr nh_;
    ros::Publisher  hello_pub_;


};

#endif // MASTERGUI_H
