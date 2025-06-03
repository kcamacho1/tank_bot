#include <Adafruit_MotorShield.h>
// Include additional software 'libraries' to control a servo motor
#include <Servo.h>
 
Servo myservo;  // create servo object called 'myservo' to control a servo motor
 
int pos = 0;          // Variable to store the servo position. Allowed range is 0 to 180
int wait_time = 100; // Number of milliseconds to allow servo to reach position
int rotate = 45;
 
const int trigPin = 11;
const int echoPin = 12;
const int buzzerPin = 3; // Digital pin connected to the Passive Buzzer module
 
// defines variables
long duration;
int distance;
 
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *Motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *Motor4 = AFMS.getMotor(4);
 
//SETUP
void setup() {
  pinMode(trigPin, OUTPUT);// Sets the trigPin (11) as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin (12) as an Input
  Serial.begin(9600); // Starts the serial communication
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(4, OUTPUT);
  
  if (!AFMS.begin()) {
  }
 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode (9, OUTPUT);
 
  pinMode(buzzerPin, OUTPUT); // Set the BuzzerPin (3) as OUTPUT
  pos=90;
}
 
//LOOP
 
void loop()
{
  checkDistance();
 
  // Call the function to play different sounds or melodies
  //LED Light
  digitalWrite(4, LOW);
 
  //forward
  Motor1->setSpeed(140);
  Motor2->setSpeed(140);
  Motor3->setSpeed(155);
  Motor4->setSpeed(155);
 
  Motor1->run(BACKWARD);
  Motor2->run(FORWARD);
  Motor3->run(BACKWARD);
  Motor4->run(FORWARD);
 
  myservo.write(pos);    // tell servo to go to position in variable 'pos'
  delay(wait_time);      // Delay, with 'wait_time' in milliseconds
  if (pos == 180) {
    rotate = -45;
  } else if (pos == 0) {
    rotate = 45;
  }
  pos = pos + rotate;
 
  checkDistance();
 
  if (distance <= 50)
  {    
    //stop
    Motor1->setSpeed(0);
    Motor2->setSpeed(0);
    Motor3->setSpeed(0);
    Motor4->setSpeed(0);
 
    Motor1->run(BRAKE);
    Motor2->run(BRAKE);
    Motor3->run(BRAKE);
    Motor4->run(BRAKE);
    delay(500);  
 
    // have the tank look around
    pos = 0;
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(500);     
 
    pos = 180;
    myservo.write(pos);    
    delay(500);     
 
    pos = 90;  //  have turret fave forward
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(500);      // Delay, with 'wait_time' in milliseconds
 
    digitalWrite(4, HIGH);
    delay(10);
    digitalWrite(4, LOW);
    delay(1);
 
    playSound();
    //delay(420); // Wait for 3 second before playing the sound again
    
    Motor1->setSpeed(250);
    Motor2->setSpeed(250);
    Motor3->setSpeed(250);
    Motor4->setSpeed(250);
  
 
    Motor1->run(FORWARD);
    Motor2->run(BACKWARD);
    Motor3->run(FORWARD);
    Motor4->run(BACKWARD);
    delay(50);
 
    Motor1->setSpeed(250);
    Motor2->setSpeed(250);
    Motor3->setSpeed(250);
    Motor4->setSpeed(250);
 
    Motor1->run(BACKWARD);
    Motor2->run(FORWARD);
    Motor3->run(BACKWARD);
    Motor4->run(FORWARD);
    delay(50);
 
    Motor1->setSpeed(0);
    Motor2->setSpeed(0);
    Motor3->setSpeed(0);
    Motor4->setSpeed(0);
 
    Motor1->run(BRAKE);
    Motor2->run(BRAKE);
    Motor3->run(BRAKE);
    Motor4->run(BRAKE);
    delay(1000);  
 
    Motor1->setSpeed(140);
    Motor2->setSpeed(140);
    Motor3->setSpeed(155);
    Motor4->setSpeed(155);
 
    Motor1->run(FORWARD);
    Motor2->run(BACKWARD);
    Motor3->run(FORWARD);
    Motor4->run(BACKWARD);
    delay(600);
 
    Motor1->setSpeed(140);
    Motor2->setSpeed(140);
    Motor3->setSpeed(140);
    Motor4->setSpeed(140);
      //turning right 90deg
    Motor1->run(FORWARD);
    Motor2->run(BACKWARD);
    Motor3->run(BACKWARD);
    Motor4->run(FORWARD);
    delay(600);
  }
}
 
void playSound() {
  // Little gunshot sounds
  int melody[] = {  // Notes of the melody (pitches)
    500, 4500, 500, 500, 500, 50,
  };
 
  int noteDuration[] = { // Duration of each note (milliseconds)
    50, 70, 50, 50, 50, 150,
      };
 
  for (int i = 0; i < 6; i++) {
    if (melody[i] == 0) {
      noTone(buzzerPin); // Turn off the buzzer if there's no note
    } else {
      tone(buzzerPin, melody[i], noteDuration[i]); // Play the note
    }
    delay(noteDuration[i] * .50); // Pause between notes to avoid overlapping
  }
  noTone(buzzerPin); // Ensure the buzzer is off at the end
}
 
void checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  Serial.println(distance);
}
