//#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
#include <Wire.h>  // I2C communication
#include <LiquidCrystal_I2C.h>  // librar for I2C 2 row x 16 column LCD
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 column and 4 line display

const int echoPin=3;
const int trigPin=4;
float duration, distance;  

const int baudRate = 9600;
long time;
// const int baudRate = 115200;

// accelerometer variables
const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ; //linear acceleration
//float GyroX, GyroY, GyroZ; //angular velocity
//float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ; //used in void loop()
//float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;

float elapsedTime, currentTime, previousTime;
int c = 0;
float proportionalRate = .5; //speed adjustment per degree of error
float maxRate = 120;
long int maxDuration = 600000;  // run duration in ms

const int maxSpeed = 255; //max PWM value written to motor speed pin. It is typically 255.
const int minSpeed = 140; //min PWM value at which motor moves

float currentAngle; //if MPU6050 is flat, angle = Z = yaw
float targetAngle = 0;
float deltaAngle;
int targetSpeed = 0;
int speedCorrection;
int correctionAngle;
float angleTolerance = 10;
int dataIsSpeed = 0;
int dataIsAngle = 0;
// lcd display variables
int spdRow=0, spdCol=14, tarRow=3,tarCol=14,actRow=1,actCol=14, corrRow=2, corrCol=14;


// for an H bridge with single pin direction control, use only pins left1 and right1
//const int left1 = 4;  //for L298N control
const int left1 = 7; // MD20A control
const int left2 = 8;     // ignored in MD20A
//const int right1 = 7;   // for L298n control
const int right1 = 9;  // for MD20A
const int right2 = 10;    // ignored in MD20A

//int rightForward = 10; //7
//int rightReverse = 9; //6
//int rightEnable = 11; //3

//int leftReverse = 8; //7
//int leftForward = 7; //6
//int leftEnable = 6; //3



// const int leftSpeed = 10;  // L298N
const int leftEnable = 6;      // MD20A
// const int rightSpeed = 11;   //L298N
const int rightEnable = 11;   // MD20A

int leftSpeedVal, rightSpeedVal;

// *** variables for new readSerial2.h
const byte buffSize = 40;
char inputBuffer[buffSize];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;
long int readValue, actValue; // maximum value of an standard integer is 32767.   
char messageFromPC[buffSize] = {0};

// **** end new variable block

//#include "gyro.h"
#include "movement.h"
//#include "readSerial.h"
//#include "readSerial2.h"


// delaring variables for readSerial3 library
const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
#include "readSerial3.h"   // read serial function from arduino website
#include "compassRead.h"   // read azimuth angle from compass chip
#include "LCDStatus.h"     // library to write to LCD display



const int buttonPin = 2;

void setupa() {
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  

  time=millis();
  Serial.begin(baudRate);
  //Serial.println("started");
  // setup I2C communication with accelerometer
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission
  // Call this function if you need to get the IMU error values for your module
 // calculateError();
  // initialize compass - define I2S and error
  compassSetup();
  // get the initial compass angle
  currentAngle = readCompassAzimuth();
  
  pinMode(right1, OUTPUT);
  digitalWrite(right1,LOW);
  pinMode(right2, OUTPUT);
  digitalWrite(right2,LOW);
  pinMode(rightEnable, OUTPUT);
  
  pinMode(left1, OUTPUT);
  digitalWrite(left1,LOW);
  pinMode(left2, OUTPUT);
  digitalWrite(left2,LOW);
  pinMode(leftEnable, OUTPUT); 


  // setup LCD Display
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on

  pinMode(buttonPin,INPUT);   // start button on Aduino
  Serial.println("<Arduino is ready>");
  analogWrite(leftEnable, 100);  
  analogWrite(rightEnable, 100); 
  //spdRow = 0;
  //lcd.setCursor(0,spdRow);
  //lcd.print("Target speed");
  //spdCol = 14;
  //lcd.setCursor(spdCol,spdRow);
  //lcd.print(targetSpeed);
  /*
  lcdStatus(14,0,"Target speed", float(targetSpeed));
  lcdStatus(14,1,"Current A", float(currentAngle));
  lcdStatus(14,2,"Correction A",float(correctionAngle));
  */
  targetAngle = currentAngle + correctionAngle;
  //lcd.print(targetAngle);
  lcdStatus(14,3,"Target A ",float(targetAngle));
  delay(1000);
  
  
}
