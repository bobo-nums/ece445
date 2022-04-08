#include <SharpIR.h>
#include <DHT20.h>
#include <util/delay.h>

#define PHOTO_PIN A0
#define IR_PIN A1
#define RED_LED_PIN 5
#define YELLOW_LED_PIN 9
#define GREEN_LED_PIN 6
#define WALK_LED_PIN 10
#define BIKE_INT_PIN 8
#define IR_SENSOR_MODEL 100500

const int ir_distance = 8; //8 ft?
int light_val;
int brightness = 255;
unsigned long time_now;
int ir_val;
bool waitingCars = true;
bool yellowState = false;
float humidity_val;
DHT20 dht;
SharpIR irSensor = SharpIR(IR_PIN,IR_SENSOR_MODEL);
volatile bool gotInterrupt = false;

const unsigned long red_delay = 4000;   //90000, 1:30 min
const unsigned long green_delay = 4000;
const unsigned long yellow_delay = 1000;

ISR (PCINT0_vect) 
{
//  if(digitalRead(BIKE_INT_PIN)){
////    analogWrite(10, 255);
//    //TODO: add interrupt routine to let pedestrians cross
//    gotInterrupt = true;
//  }
  gotInterrupt = true;
} 

void RedLight(){
  analogWrite(RED_LED_PIN, brightness);
  //TODO: Activate IR sensor reading
//  ir_val = map(analogRead(IR_PIN), 0, 1023, 0, 255);
//  ir_val = irSensor.distance();
  time_now = millis();
//  while(ir_val > 200);
   
  while(millis() - time_now < red_delay);
  analogWrite(RED_LED_PIN, 0);
}

void YellowLight(){
  yellowState = true;
  analogWrite(YELLOW_LED_PIN, brightness);
  
  //READ PHOTORESISTOR
  light_val = map(analogRead(PHOTO_PIN), 0, 1023, 0, 255);

//--------------testing photoresistor-------------------
//  if(light_val > 130){
//    analogWrite(10, 255);
//  }
//  else{
//    analogWrite(10, 0);
//  }
//--------------------------------------------------------
  
  //Take humidity reading
//  int humidity_sensor_status = dht.read();
//  switch (humidity_sensor_status)
//  {
//    case DHT20_OK:
//      humidity_val = dht.getHumidity();
////      Serial.println(humidity_val);
//      break;
//    default:
////      Serial.print("Unknown error,\t");
//      humidity_val = 100;
//      break;
//  }

//------------------testing humidity sensor-------------
//  if(humidity_val > 60){
//    analogWrite(10, 255);
//  }
//  else{
//    analogWrite(10, 0);
//  }
//  delay(500);
//-------------------------------------------------------

  brightness = 255 - light_val; //max(0, 255 - light_val);
  delay(yellow_delay);
  analogWrite(YELLOW_LED_PIN, 0);
}


void GreenLight(){
  PCMSK0 |= B00000001; //mask interrupts on pin 14: PCINT0 
  
  analogWrite(GREEN_LED_PIN, brightness);
  
  time_now = millis();
  while(millis() - time_now < green_delay && !gotInterrupt);

  analogWrite(GREEN_LED_PIN, 0);
  
  PCMSK0 &= B00000000; //unmask interrupts
}

void setup() {
  light_val = map(analogRead(PHOTO_PIN), 0, 1023, 0, 255);
//  dht.begin();
  pinMode(WALK_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  
  analogWrite(WALK_LED_PIN, 0);
  analogWrite(RED_LED_PIN, 0);
  analogWrite(YELLOW_LED_PIN, 0);
  analogWrite(GREEN_LED_PIN, 0);
 
  PCICR |= B00000001; //Enable interrupts on port B (PCINT0-PCINT7)
  PCMSK0 &= B00000000; //unmask interrupts on all pins
}

void loop() {
  gotInterrupt = false;
  waitingCars = true;

  RedLight();
  if(waitingCars){
    GreenLight();
    YellowLight();
  }

}
