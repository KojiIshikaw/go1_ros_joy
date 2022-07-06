#include "ros/ros.h"                          // ROS Default Header File
#include "go1_ros_joy/MsgJoy.h"  // MsgTutorial Message File Header. The header file is automatically created when building the package.

// Message callback function. This is a function is called when a topic
// message named 'ros_tutorial_msg' is received. As an input message,
// the 'MsgTutorial' message of the 'ros_tutorials_topic' package is received.
void msgCallback(const go1_ros_joy::MsgJoy::ConstPtr& msg)
{
  ROS_INFO("recieve msg R1R2start = %d, %d, %d, %d, %d, %d, %d, %d",
   msg->R1, msg->L1, msg->start, msg->select, msg->R2, msg->L2, msg->F1, msg->F2);
  ROS_INFO("recieve msg ABXY = %d, %d, %d, %d, %d, %d, %d, %d",
   msg->A, msg->B, msg->X, msg->Y, msg->up, msg->right, msg->down, msg->left);
}

int main(int argc, char **argv)                         // Node Main Function
{
  ros::init(argc, argv, "topic_subscriber");            // Initializes Node Name

  ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system

  // Declares subscriber. Create subscriber 'ros_tutorial_sub' using the 'MsgTutorial'
  // message file from the 'ros_tutorials_topic' package. The topic name is
  // 'ros_tutorial_msg' and the size of the publisher queue is set to 100.
  ros::Subscriber ros_joy_sub = nh.subscribe("ros_joy_msg", 100, msgCallback);

  // A function for calling a callback function, waiting for a message to be
  // received, and executing a callback function when it is received.
  ros::spin();

  return 0;
}
