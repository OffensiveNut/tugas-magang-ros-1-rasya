#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <iostream>

using namespace std;

ros::Publisher dosen_pub; // global declaration soalnya mau dipake di fungsi FRSCallback

void FRSCallback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("FRS Mahasiswa:\n%s", msg->data.c_str());

    string feedback;
    cout << "Masukkan feedback untuk mahasiswa: ";
    getline(std::cin, feedback);

    std_msgs::String response;
    response.data = feedback;

    dosen_pub.publish(response);
    ROS_INFO("Feedback dari Dosen: %s", response.data.c_str());
}
void endCallback(const std_msgs::Empty::ConstPtr& msg) {
    ROS_INFO("Mendapatkan sinyal untuk mengakhiri program.");
    ros::shutdown(); // Menghentikan node
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "dosen");
    ros::NodeHandle nh;

    ros::Subscriber mahasiswa_sub = nh.subscribe("FRS", 1000, FRSCallback);
    ros::Subscriber end_sub = nh.subscribe("END", 1000, endCallback);
    dosen_pub = nh.advertise<std_msgs::String>("FEEDBACK", 1000);

    cout << "Menunggu FRS mahasiswa...\n";
    ros::spin(); 

    return 0;
}
