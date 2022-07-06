#include "ros/ros.h"                            // ROS Default Header File
#include "go1_ros_joy/MsgJoy.h" 

#include "unitree_legged_sdk/unitree_legged_sdk.h"
#include "unitree_legged_sdk/joystick.h"
#include <math.h>
#include <iostream>
#include <unistd.h>

using namespace UNITREE_LEGGED_SDK;

static uint8_t gl_R1;
static uint8_t gl_L1;
static uint8_t gl_start;
static uint8_t gl_select;
static uint8_t gl_R2;
static uint8_t gl_L2;
static uint8_t gl_F1;
static uint8_t gl_F2;
static uint8_t gl_A;
static uint8_t gl_B;
static uint8_t gl_X;
static uint8_t gl_Y;
static uint8_t gl_up;
static uint8_t gl_right;
static uint8_t gl_down;
static uint8_t gl_left;

class Custom
{
public:
    Custom(uint8_t level): safe(LeggedType::Go1), udp(level){
        udp.InitCmdData(cmd);
    }
    void UDPSend();
    void UDPRecv();
    void RobotControl();

    Safety safe;
    UDP udp;
    LowCmd cmd = {0};
    LowState state = {0};
    float dt = 0.002;     // 0.001~0.01
    xRockerBtnDataStruct _keyData;
};

void Custom::UDPRecv()
{ 
    udp.Recv();
}

void Custom::UDPSend()
{  
    udp.Send();
}


void Custom::RobotControl() 
{
    udp.GetRecv(state);
    memcpy(&_keyData, &state.wirelessRemote[0], 40);

    gl_R1  = (int)_keyData.btn.components.R1;
    gl_L1  = (int)_keyData.btn.components.L1;
    gl_start  = (int)_keyData.btn.components.start;
    gl_select  = (int)_keyData.btn.components.select;
    gl_R2  = (int)_keyData.btn.components.R2;
    gl_L2  = (int)_keyData.btn.components.L2;
    gl_F1  = (int)_keyData.btn.components.F1;
    gl_F2  = (int)_keyData.btn.components.F2;
    gl_A  = (int)_keyData.btn.components.A;
    gl_B  = (int)_keyData.btn.components.B;
    gl_X  = (int)_keyData.btn.components.X;
    gl_Y  = (int)_keyData.btn.components.Y;
    gl_up  = (int)_keyData.btn.components.up;
    gl_right  = (int)_keyData.btn.components.right;
    gl_down  = (int)_keyData.btn.components.down;
    gl_left  = (int)_keyData.btn.components.left;

    ROS_INFO("recv keyData.start= %d", (int)_keyData.btn.components.start;); 

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "topic_publisher");
    ros::NodeHandle nh; 
    ros::Publisher ros_joy_pub = nh.advertise<go1_ros_joy::MsgJoy>("ros_joy_msg", 100);
    ros::Rate loop_rate(100);

    go1_ros_joy::MsgJoy msg;     // Declares message 'msg' in 'MsgTutorial' message file format

    Custom custom(LOWLEVEL);
    // InitEnvironment();
    LoopFunc loop_control("control_loop", custom.dt,    boost::bind(&Custom::RobotControl, &custom));
    LoopFunc loop_udpSend("udp_send",     custom.dt, 3, boost::bind(&Custom::UDPSend,      &custom));
    LoopFunc loop_udpRecv("udp_recv",     custom.dt, 3, boost::bind(&Custom::UDPRecv,      &custom));

    loop_udpSend.start();
    loop_udpRecv.start();
    loop_control.start();

    while(ros::ok()){
        msg.R1  = gl_R1;
        msg.L1  = gl_L1;
        msg.start  = gl_start;
        msg.select  = gl_select;
        msg.R2  = gl_R2;
        msg.L2  = gl_L2;
        msg.F1  = gl_F1;
        msg.F2  = gl_F2;
        msg.A  = gl_A;
        msg.B  = gl_B;
        msg.X  = gl_X;
        msg.Y  = gl_Y;
        msg.up  = gl_up;
        msg.right  = gl_right;
        msg.down  = gl_down;
        msg.left  = gl_left;
    
        ROS_INFO("send msg start= %d", msg.start); 
        ros_joy_pub.publish(msg);
    };

    return 0; 
}

