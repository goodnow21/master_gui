#ifndef MASTERGUI_H
#define MASTERGUI_H

#include <QMainWindow>
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
  void spinOnce();

private slots:

  void on_hiButton_clicked();

private:
    Ui::MasterGui *ui;
    QTimer *ros_timer;

    ros::NodeHandlePtr nh_;
    ros::Publisher  hello_pub_;
};

#endif // MASTERGUI_H
