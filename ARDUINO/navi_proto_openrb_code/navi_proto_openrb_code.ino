#define USE_USBCON

#include <ros.h>
#include <navi_proto_humanoid_msgs/Humanoid.h>
#include <Dynamixel2Arduino.h>
#define DXL_SERIAL Serial3
#define DEBUG_SERIAL Serial
const int DXL_DIR_PIN = -1;

ros::NodeHandle  nh;
/////////////////////////////////////////////////////////////

const uint8_t DXL_ID_9 = 9;
const uint8_t DXL_ID_8 = 8;

////////////////////////////////////////////////////////////

int DXL_POSITION_9= 2040;
int DXL_POSITION_8= 2040;
int DXL_POSITION_7= 1246;
int DXL_POSITION_6= 1246;
int DXL_POSITION_5= 2040;
int DXL_POSITION_4= 2040;
int DXL_POSITION_3= 2040;
int DXL_POSITION_2= 2040;

////////////////////////////////////////////////////////////
const float DXL_PROTOCOL_VERSION = 2.0;
const uint32_t DXL_BAUD_RATE = 1000000;
const uint8_t DXL_CONTROL_SPEED = 0;
////////////////////////////////////////////////////////////

Dynamixel2Arduino dxl_9(DXL_SERIAL, DXL_DIR_PIN);
Dynamixel2Arduino dxl_8(DXL_SERIAL, DXL_DIR_PIN);

////////////////////////////////////////////////////////////
//This namespace is required to use Control table item names
using namespace ControlTableItem;


void navi_control_callback( const navi_proto_humanoid_msgs::Humanoid& msg){
  DXL_POSITION_8=msg.servo_head[0];
  DXL_POSITION_9=msg.servo_head[1];

  if(DXL_POSITION_9 > 2000){
    digitalWrite(32, HIGH);
  }
  else{
    digitalWrite(32, LOW);
  }


  //dxl_9.setGoalPosition(DXL_ID_9, DXL_POSITION_9);
  //dxl_8.setGoalPosition(DXL_ID_8, DXL_POSITION_8);
}


ros::Subscriber<navi_proto_humanoid_msgs::Humanoid> sub("/navi/openrb", navi_control_callback);

void setup(){
  nh.initNode();
  nh.subscribe(sub);
  DEBUG_SERIAL.begin(115200);
  DXL_setup();

  pinMode(32,OUTPUT);
}

void loop(){
  nh.spinOnce();
  delay(1);
}

//////////////////////////////////////////////////////////////////////////

void DXL_setup(){
  dxl_9.begin(DXL_BAUD_RATE);
  dxl_8.begin(DXL_BAUD_RATE);
  
  dxl_9.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl_8.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  
  dxl_9.ping(DXL_ID_9);
  dxl_8.ping(DXL_ID_8);
  
  dxl_9.torqueOff(DXL_ID_9);
  dxl_8.torqueOff(DXL_ID_8);
  
  dxl_9.setOperatingMode(DXL_ID_9, OP_POSITION);
  dxl_8.setOperatingMode(DXL_ID_8, OP_POSITION);
  
  dxl_9.torqueOn(DXL_ID_9);
  dxl_8.torqueOn(DXL_ID_8);
  
  dxl_9.writeControlTableItem(PROFILE_VELOCITY, DXL_ID_9, DXL_CONTROL_SPEED);
  dxl_8.writeControlTableItem(PROFILE_VELOCITY, DXL_ID_8, DXL_CONTROL_SPEED);
}
