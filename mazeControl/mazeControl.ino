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
/*
float currentAngle; //if MPU6050 is flat, angle = Z = yaw
float targetAngle = 0;
float deltaAngle;
int targetSpeed = 0;
int speedCorrection;
int correctionAngle; 
float angleTolerance = 7.0;*/


void loop() {
  currentAngle = readCompassAzimuth();
  time=millis();
  targetSpeed=120;
  targetAngle=90;
  //correctionAngle = 90;
  moveControl();
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
  lcdStatus(spdCol,spdRow,"TargetSpeed",float(targetSpeed));
  lcdStatus(actCol,actRow,"Current A",float(currentAngle));
  lcdStatus(corrCol,corrRow,"Correction A",float(correctionAngle));
  lcdStatus(tarCol,tarRow,"Target A",float(targetAngle));

  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);  
  distance = (duration*.0343)/2;  
  //Serial.print("Distance: ");  
	Serial.println(distance);  
	delay(100);  


  }
