//#define USE_USBCON

#include <ros.h>
#include <navi_proto_humanoid_msgs/Humanoid.h>

ros::NodeHandle  nh;


void navi_control_callback( const navi_proto_humanoid_msgs::Humanoid& angle_msg){

}


ros::Subscriber<navi_proto_humanoid_msgs::Humanoid> sub("navi/openrb", navi_control_callback);

void setup(){
  nh.initNode();
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
  delay(1);
}
