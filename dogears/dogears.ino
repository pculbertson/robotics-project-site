#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

uint16_t state;

void messageRead(const std_msgs::UInt16& msg) {
  state = msg.data;
}

ros::NodeHandle nh;

Servo servoLeft;
Servo servoRight;

ros::Subscriber<std_msgs::UInt16> sub("turtlebot_follower/ears", &messageRead);

//what is second argument where 'state' is written?
//if this subscribes to topic, how do you declare a variable name?
//also, what's a callback?

void setup() {
  Serial.begin(9600);
  servoLeft.attach(9);
  servoRight.attach(10);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  if(state==1)
  {
    dogFollow();
  }
  else if(state==0)
  {
    dogStay();
  }
  nh.spinOnce();
  delay(1);
}

void dogFollow() {
  servoLeft.write(159);
  servoRight.write(74);
  delay(250);
  servoLeft.write(151);
  servoRight.write(82);
  delay(250);
}

void dogStay() {
  servoLeft.write(175);
  servoRight.write(45);
}

void dogRollOver() {
  servoLeft.write(120);
  servoRight.write(100);
}
