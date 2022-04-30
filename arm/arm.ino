
#include <math.h>
#include <Servo.h>

#include <SPI.h>
#include <RF24.h>

//nrf declaration
RF24 radio(8,9);
const byte address[6] = "45678";

//declare servos
Servo base;
Servo armOne;
Servo armTwo;
Servo grip;

float baseAngle;
float armOneAngle;
float armTwoAngle;

//declare arm dimensions
float a1 = 88;
float a2 = 74;
float a3 = 91 ;

float x = 100;
float y = 100;
float z = 100;

float xspeed = 0;
float yspeed = 0;
float zspeed = 0;

//create and declare data type for analog sticks
struct coordinates {
  float x;
  float y;
  float z;
  bool grip;
  bool control;
};
typedef struct coordinates coordinates;
coordinates coords;
bool gripstate;

void setup() {
  Serial.begin(115200);       
  base.attach(2);
  armOne.attach(3);
  armTwo.attach(4);
  grip.attach (5);

  radio.begin();               
  radio.setChannel(110);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, address[0]);
  radio.startListening();

}

void loop() {
  //read xyz speed from remote
  if (radio.available()){
    while(radio.available()){
      radio.read(&coords, sizeof(coords));
    }
  }
  
  //apply speed to arm
  if (coords.control == true){
    //reset movement speed
    xspeed = 0;
    yspeed = 0;
    zspeed = 0;
    //set new speed
    xspeed = (coords.x-517)/2000;
    yspeed = (coords.y-525)/2000;
    zspeed = (coords.z-528)/1500;
    //move according to speed
    x = constrain((x - xspeed), 1, 200);
    y = constrain((y + yspeed), 1, 200);
    z = constrain((z + zspeed), 1, 250);  
    gripstate = coords.grip;
    Serial.println(gripstate);
    if (gripstate == true) {
      grip.write(0);
      //Serial.println("closed");
    }
    else{
      grip.write(90);
      //Serial.println("open");
    }
  }
  
  //read xyz from knobs
  else{
    z = ((analogRead(A0)/3)+1);
    y = ((analogRead(A1)/6)+1);
    x = ((analogRead(A2)/6)+1);
    grip.write(analogRead(A4)/9);
  }

  //inverse kinematics equations
  float t1 = atan(y/x);//1
  float r1 = sqrt(sq(x)+sq(y));//2
  float r2 = z - a1;//3
  float f2 = atan(r2/r1);//4
  float r3 = sqrt(sq(r1)+sq(r2));//5
  float f1 = acos((sq(a3)-sq(a2)-sq(r3))/((-2)*a2*r3));//6
  float t2 = f1 + f2;//7
  float f3 = acos((sq(r3)-sq(a2)-sq(a3))/((-2)*a2*a3));//8
  float t3 = 3.1416 - f3;//9

  //convert angles to degrees and compensate for gearing
  baseAngle = (2 * (1.5708-t1) * 57.2958);
  armOneAngle = (2 * (1.5708-t2) * 57.2958);
  armTwoAngle = (2 * t3 * 57.2958);
  
  //set angles on motors
  base.write(baseAngle);
  armOne.write(armOneAngle);
  armTwo.write(armTwoAngle);
  
  
}
