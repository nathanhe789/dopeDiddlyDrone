//Names: Nathan He, Fernando Avila, Carson Chang, Cynthia Martinez
//CS362 Projects

//set RGB pins
const int redPin1 = 11;
const int greenPin1 = 10;
const int bluePin1 = 9;

//set RGB Level
int rVal = 250;
int gVal = 5;
int bVal = 127;

//set RGB direction
int rDir = -1;
int gDir = 1;
int bDir = -1;

//------------------------------------------------------
//Ultrasonic Sensor
const int trigPin = 7;
const int echoPin = 6;

long duration, cm, inches;

//------------------------------------------------------


void setColor1(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin1, redValue);
  analogWrite(greenPin1, greenValue);
  analogWrite(bluePin1, blueValue);
}

//fade tgb leds
void fade1() {
  //start fade
  rVal = rVal + rDir;
  gVal = gVal + gDir;
  bVal = bVal + bDir;
 
  //check direction
  if(rVal >= 255 || rVal <= 0) {
    rDir *= -1;
  }

  if(gVal >= 255 || gVal <= 0) {
    gDir *= -1;
  }

  if(bVal >= 255 || bVal <= 0) {
    bDir *= -1;
  }
}

//helper function to convert duration to inches
long microsecondsToInches(long microseconds) { return microseconds / 74 / 2; }

//helper function to convert duration to inches
long microsecondsToCentimeters(long microseconds) { return microseconds / 29 / 2; }

//function to get duration
void getDuration() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  // Prints the distance on the Serial Monitor
   //Serial.print(inches);
   //Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();

}

//function to sense object
void senseObject() {
  //long ft = inches / 12;
  if (cm <= 8) {
    //set red
    setColor1(255, 0, 0);
  }else if(cm > 8 && cm <= 15) {
    //set orange
    setColor1(255, 165, 0);
  } else {
    setColor1(0, 255, 0);  
  }
  
}

void setup() {
  //Set up serial communication
  Serial.begin(9600);
  
  //Set up RGB pins
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);

  //Set up trigger and echo pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  setColor1(rVal, gVal, bVal);
  //fade1();

  senseObject();
 
  getDuration();

  //delay(100);
}
