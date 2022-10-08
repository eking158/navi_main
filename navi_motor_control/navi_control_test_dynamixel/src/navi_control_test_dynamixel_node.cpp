#include <iostream>
#include <ros/ros.h>
#include <navi_proto_humanoid_msgs/Humanoid.h>
#include <stdio.h>
#include "dynamixel_sdk_examples/SyncSetPosition.h"

ros::Publisher ControlPublisher; //init publisher
ros::Subscriber GetDataSubscriber; //init subscriber

void counterCallback(const navi_proto_humanoid_msgs::Humanoid& msg){
    dynamixel_sdk_examples::SyncSetPosition motor;
    motor.id2=2;
    motor.id3=3;
    motor.id4=4;
    motor.id5=5;
    motor.id6=6;
    motor.id7=7;
    motor.id8=8;
    motor.id9=9;

    motor.position2=msg.servo_left[0];
    motor.position4=msg.servo_left[1];
    motor.position6=msg.servo_left[2];

    motor.position3=msg.servo_right[0];
    motor.position5=msg.servo_right[1];
    motor.position7=msg.servo_right[2];

    motor.position8=msg.servo_head[0];
    motor.position9=msg.servo_head[1];

    ControlPublisher.publish(motor);
}

int main(int argc, char** argv)
{
  //init the ROS node
  ROS_INFO_STREAM("scanning...");
  ros::init(argc, argv, "navi_control_test_dynamixel_node");  //init node
  ros::NodeHandle nodeHandle;
  //operatorPublisher = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel",1);
  GetDataSubscriber = nodeHandle.subscribe("/navi/unity",1000,counterCallback);
  ControlPublisher = nodeHandle.advertise<dynamixel_sdk_examples::SyncSetPosition>("/dynamicxel_set_position",1);
  ros::spin();
  return 0;
}
