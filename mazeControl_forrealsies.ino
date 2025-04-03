/*   Drive Control 2
By Chris Fischer
Based on Drive Control -- same principal, but cleaned up
Read data from serial and use to control direction and speed.
Direction is compared to a MPU6050 6 axis accelerometer
Nominal speed is controlled by motor PWM controls

Speed is coded as 10xxx where xxx is speed (max 255)
Angle is coded as 20xxx where xxx is the target angle (0-359)

Ascii values should be sent with '<' and '>' as start and end 
characters, respectively.

So a speed of 155 should use the ascii string
<10155>
An angle of 97 should use the ascii string
<20097>

*/
#include "Setup.h"

void setup() {
  setupa();
  queue("front","left"); 

  /*
  targetSpeed = 0;
  targetAngle = currentAngle+90;
  while (currentAngle > targetAngle + 10 || currentAngle < targetAngle - 10){
    currentAngle = readCompassAzimuth();
    moveControl();
  }
  */
  
  queue("front", "left"); //6
  queue("front", "right"); //7
  queue("front", "left"); //8
  queue("right", "right"); //9
  queue("front", "right"); // 10

  queue("right", "right"); //12
  queue("front", "left"); //13
  queue("front", "right"); //14
  queue("front", "left"); //17
  queue("front", "left"); // 19

  queue("right", "right"); //22
  queue("left", "left"); //24
  queue("front", "left"); //26
  queue("front", "right"); //28
  queue("front", "left"); //29
  queue("right", "right"); //30
  queue("front", "left"); //31
  queue("right", "right"); //32
  queue("front", "right"); //33
  queue("front", "left"); //38
  queue("front", "left"); //39
  queue("front", "left"); //END!!!!!!
  
}


void queue(String boundary, String turn) {
  int startAngle = readCompassAzimuth();
  targetAngle = currentAngle;
  targetSpeed=120;
  if(boundary.equals("front")){
    while(distanceSensor()>6 || distanceSensor()>1000){
      currentAngle = readCompassAzimuth();
      moveControl();
      Serial.println(distanceSensor());
    }
  }
  if(boundary.equals("left")){
    while(distanceSensorLeft()<10 || distanceSensor()>1000){
      currentAngle = readCompassAzimuth();
      moveControl();
    }
  }
   if(boundary.equals("right")){
    while(distanceSensorRight()<10|| distanceSensor()>1000){
      currentAngle = readCompassAzimuth();
      moveControl();
    }
  }
  turnFunc(turn);
  stopCar();
}
  
  

void turnFunc(String turn){
  Serial.println("turning!!");
  int startAngle = readCompassAzimuth();
  targetSpeed = 0;
  if(turn.equals("left")){
    targetAngle = currentAngle+80;
  }
  else{//(turn.equals("right"))
    targetAngle = currentAngle-80;
    //targetAngle = currentAngle+90;
  }
  
  //abs(currentAngle - targetAngle) < 1
  int driveTime = 2000;
  int startTime = millis();
  while (time < startTime+driveTime && currentAngle - targetAngle != 0) {
    time = millis();
    currentAngle = readCompassAzimuth();
    moveControl();
    correctionAngle = findCorrectionAngle(currentAngle, targetAngle);
  }
}


void loop(){
  /*
  Serial.print("left: ");
  Serial.println(distanceSensorLeft());
  Serial.print("right: ");
  Serial.println(distanceSensorRight());
  Serial.print("fwd: ");
  Serial.println(distanceSensor());
  */
};  // loop function has to exist even if it is empty

/*
  if(time>10000){
    moveControl();
  }else{
    stopCar();
  }
  */
    /*digitalWrite(rightEnable,HIGH);
    digitalWrite(leftEnable,HIGH); 
    analogWrite(right1, 255);
    analogWrite(right2, 0);
    analogWrite(left2, 255);
    analogWrite(left1, 0);*/
  
  // compare current speed and direction to target speed and direction
  // if they don't match, call moveContol
 /*

 Serial.begin(9600);
  int startAngle = readCompassAzimuth();
  targetAngle = currentAngle;
  int driveTime = 30000;
  int startTime = millis();
  while (time < startTime+driveTime ) { //&& distanceSensor()>10
    currentAngle = readCompassAzimuth();
    time=millis();
    targetSpeed=120;
    //targetAngle=currentAngle;
    //Serial.print("left: ");
    //Serial.println(distanceSensorLeft());
    Serial.print("right: ");
    Serial.println(distanceSensorRight());
    //Serial.print("fwd: ");
    //Serial.println(distanceSensor());
    
    lcdStatus(spdCol,spdRow,"Right S",float(rightSpeedVal));
    lcdStatus(actCol,actRow,"Left S",float(leftSpeedVal));
    lcdStatus(corrCol,corrRow,"Correction A",float(correctionAngle));
    lcdStatus(tarCol,tarRow,"Current Angle",float(currentAngle));

    Serial.print("target: ");
    Serial.println(targetAngle);
    Serial.print("current: ");
    Serial.println(currentAngle);
    Serial.print("left: ");
    Serial.println(leftSpeedVal);
    Serial.print("right: ");
    Serial.println(rightSpeedVal);
    
    //correctionAngle = 90;

    moveControl();
   // Serial.print(CorrectionAngle);
  }
  */