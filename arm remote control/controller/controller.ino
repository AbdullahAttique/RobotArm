

#include <SPI.h>
#include <RF24.h>

//nrf declaration
RF24 radio(8, 9);
const byte address[6] = "45678";

//joystick declaration
const int l_swpin = 5;//left button pin
const int r_swpin = 6;//right button pin

const int lx_pin = 3;//left axis analog pins
const int ly_pin = 2;

const int rx_pin = 1;//right axis analog pins
const int ry_pin = 0;

bool control = false;//dictates if controller is active

//create and declare data type for coordinates
struct coordinates {
  float x;
  float y;
  float z;
  bool grip;
  bool control;
};
typedef struct coordinates coordinates;
coordinates coords;

bool grip = 0;


//toggle switch
int switchpin = 4;

void setup() {
  //initialise toggle switch
  pinMode (switchpin, INPUT);
  digitalWrite(switchpin, HIGH);

  //nrf initialise
  radio.begin();
  radio.setChannel(110);  
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address[0]);
  radio.stopListening();
  
  //joystick initialise
  pinMode(l_swpin, INPUT);
  pinMode(r_swpin, INPUT);
  digitalWrite(l_swpin, HIGH);
  digitalWrite(r_swpin, HIGH);

  Serial.begin(115200);
}

void loop() {

  Serial.print("Lx:");
  Serial.println(analogRead(lx_pin));

  Serial.print("Ly:");
  Serial.println(analogRead(ly_pin));

  Serial.print("Rx:");
  Serial.println(analogRead(rx_pin));

  Serial.print("Ry:");
  Serial.println(analogRead(ry_pin));

  if (digitalRead(r_swpin) == LOW){
    grip = !grip;
    while (digitalRead(r_swpin) == LOW){
      delay(50);
    }
  }
  Serial.println(grip);
  
  if (digitalRead(switchpin) == HIGH){
    control = true;
  }
  else{
    control = false;
  }
  coords = {analogRead(lx_pin), analogRead(ly_pin), analogRead(ry_pin), grip, control};
  radio.write(&coords, sizeof(coords));
}
