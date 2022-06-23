#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "opencv2/highgui/highgui.hpp"
#include "cv_bridge/cv_bridge.h"

using namespace std;
using namespace cv;

void receiveCallBack(const sensor_msgs::ImageConstPtr& msg) // callback func body
{
    ROS_INFO("width is : [%d] height is : [%d]", msg->width, msg->height); // print out current importing img size
    Mat image = cv_bridge::toCvShare(msg, "bgr8")-> image; // save the img to local variable
    Mat gray_img; // name a new variable for further use
    cvtColor(image, gray_img, COLOR_BGR2GRAY); // convert img color from original BGR to GRAY color mode

    namedWindow("preview", CV_WINDOW_NORMAL); // pre-define a new flexible window
    resizeWindow("preview", 1280, 720);
    cv::imshow("preview", gray_img); // show the converted img
    waitKey(400); // delay 10ms
    destroyAllWindows(); // destroy the window
}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "subscriber"); // initialize ros node
  ros::NodeHandle nodeHandle; // set up ros node handle
  ROS_INFO("started listening topic..."); // send info level message to ...

  ros::Subscriber subscriber = nodeHandle.subscribe( //set up a subscriber to listen from the topic
          "/pylon_camera_node/image_raw",  // topic name from the bag file
          1000,
          receiveCallBack); // callback func name
  ros::spin(); // keep the program working endlessly
  return 0;
}