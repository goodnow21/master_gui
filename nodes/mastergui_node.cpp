#include "mastergui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "master_gui_node");
    QApplication a(argc, argv);


    MasterGui w;
    w.show();

    return a.exec();
}
