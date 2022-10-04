#include <iostream>
#include <ros/ros.h>
#include <navi_old_humanoid_msgs/Humanoid.h>
#include <stdio.h>
#include "dynamixel_sdk_examples/SyncSetPosition.h"

ros::Publisher ControlPublisher; //init publisher
ros::Subscriber GetDataSubscriber; //init subscriber

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void counterCallback(const navi_old_humanoid_msgs::Humanoid& angle_data){
    ROS_INFO("servo_head_1: %f", angle_data.servo_head.servo1);
    ROS_INFO("servo_head_2: %f", angle_data.servo_head.servo2);
    ROS_INFO("servo_head_3: %f", angle_data.servo_head.servo3);

    ROS_INFO("servo_Left_Arm_1: %f", angle_data.servo_left.servo1);
    ROS_INFO("servo_Left_Arm_2: %f", angle_data.servo_left.servo2);
    ROS_INFO("servo_Left_Arm_3: %f", angle_data.servo_left.servo3);
    ROS_INFO("servo_Left_Arm_4: %f", angle_data.servo_left.servo4);
    ROS_INFO("servo_Left_Arm_5: %f", angle_data.servo_left.servo5);
    ROS_INFO("servo_Left_Arm_6: %f", angle_data.servo_left.servo6);
    ROS_INFO("servo_Left_Arm_7: %f", angle_data.servo_left.servo7);

    ROS_INFO("servo_Right_Arm_1: %f", angle_data.servo_right.servo1);
    ROS_INFO("servo_Right_Arm_2: %f", angle_data.servo_right.servo2);
    ROS_INFO("servo_Right_Arm_3: %f", angle_data.servo_right.servo3);
    ROS_INFO("servo_Right_Arm_4: %f", angle_data.servo_right.servo4);
    ROS_INFO("servo_Right_Arm_5: %f", angle_data.servo_right.servo5);
    ROS_INFO("servo_Right_Arm_6: %f", angle_data.servo_right.servo6);
    ROS_INFO("servo_Right_Arm_7: %f", angle_data.servo_right.servo7);

    dynamixel_sdk_examples::SyncSetPosition motor;
    motor.id1=1;
    motor.id2=2;
    motor.id3=3;
    motor.id4=4;
    motor.id5=5;
    motor.id6=6;
    motor.id7=7;

    motor.position1=(int)map(angle_data.servo_left.servo1,0,360,0,1000);
    motor.position3=(int)map(angle_data.servo_left.servo2,0,360,0,1000);
    motor.position5=(int)map(angle_data.servo_right.servo1,0,360,0,1000);
    motor.position7=(int)map(angle_data.servo_right.servo2,0,360,0,1000);

    ControlPublisher.publish(motor);
}

int main(int argc, char** argv)
{
  //init the ROS node
  ROS_INFO_STREAM("scanning...");
  ros::init(argc, argv, "navi_control_test_dynamixel_node");  //init node
  ros::NodeHandle nodeHandle;
  //operatorPublisher = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel",1);
  GetDataSubscriber = nodeHandle.subscribe("/NAVI_angles",1000,counterCallback);
  ControlPublisher = nodeHandle.advertise<dynamixel_sdk_examples::SyncSetPosition>("/dynamicxel_set_position",1);
  ros::spin();
  return 0;
}
