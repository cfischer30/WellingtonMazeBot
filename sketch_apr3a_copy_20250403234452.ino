
void turnFunc();

const int echoPin=2;
const int trigPin=5;
const int echoPinLeft=4;
const int trigPinLeft=3; 
const int echoPinRight=12;
const int trigPinRight=13;

float duration, distance;  
float durationLeft,distanceLeft;
float durationRight,distanceRight;



void setup() {
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  

  pinMode(trigPinLeft, OUTPUT);  
	pinMode(echoPinLeft, INPUT);  

  pinMode(trigPinRight, OUTPUT);  
	pinMode(echoPinRight, INPUT);  

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("left: ");
  Serial.println(distanceSensorLeft());
  Serial.print("right: ");
  Serial.println(distanceSensorRight());
  Serial.print("fwd: ");
  Serial.println(distanceSensor());
  }



int distanceSensor(){
  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);  
  distance = (duration*.0343)/2;  
	return(distance);
}
int distanceSensorLeft(){
  digitalWrite(trigPinLeft, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPinLeft, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPinLeft, LOW);  
  durationLeft = pulseIn(echoPinLeft, HIGH);  
  distanceLeft = (durationLeft*.0343)/2;  
	return(distanceLeft);
}
int distanceSensorRight(){
  digitalWrite(trigPinRight, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPinRight, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPinRight, LOW);  
  durationRight = pulseIn(echoPinRight, HIGH);  
  distanceRight = (durationRight*.0343)/2;  
	return(distanceRight);
}
