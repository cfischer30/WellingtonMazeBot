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
 

 Serial.begin(9600);
  int startAngle = readCompassAzimuth();
  //targetAngle = currentAngle;
  int driveTime = 20000;
  int startTime = millis();
  while (time < startTime+driveTime) { //&& distanceSensor()>10
    currentAngle = readCompassAzimuth();
    time=millis();
    targetSpeed=0;
    targetAngle=startAngle;
    Serial.println(distanceSensorLeft());
    /*
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
    */
    //correctionAngle = 90;
    moveControl();

  }
  //stopCar();
  /*
  targetAngle=currentAngle+90;
  startTime = millis();
  while (time < startTime+driveTime) {
    currentAngle = readCompassAzimuth();
    time=millis();
    targetSpeed=0;
    lcdStatus(spdCol,spdRow,"Right S",float(rightSpeedVal));
    lcdStatus(actCol,actRow,"Left S",float(leftSpeedVal));
    lcdStatus(corrCol,corrRow,"Correction A",float(correctionAngle));
    lcdStatus(tarCol,tarRow,"Current Angle",float(targetAngle));
    //correctionAngle = 90;
    moveControl();
  }
  */
  stopCar();
  
}

void loop() {
  
  }