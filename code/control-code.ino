#include <DHT20.h>
#define PHOTO_PIN A0
#define IR_PIN 10
#define RED_LED 3
#define YELLOW_LED 4
#define GREEN_LED 5
#define WALK_LED 10
#define BIKE_INT_PIN 8

const int ir_distance = 8; //8 ft?
const int green_period = 90000;
unsigned long time_now = 0;
int light_val;
bool waitingCars = true;
float humidity_val;
DHT20 dht;
volatile bool gotInterrupt = false;

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
//  digitalWrite(RED_LED, HIGH);
  //TODO: Add IR sensor reading
//   ir_val = analogRead(IR_PIN);
//  if(ir_val > ir_distance){
//    waitingCars = true;
//  }
//   analogWrite(10, 0);
//   while(millis() - time_now > 5000){
//    time_now = millis();
//   }
//  delay(1000);
//  delay(90000);
}

void YellowLight(){
//  yellowState = true;
//  digitalWrite(GREEN_LED, LOW);
//  digitalWrite(YELLOW_LED, HIGH);
  
  //READ PHOTORESISTOR
//  light_val = map(analogRead(PHOTO_PIN), 0, 1023, 0, 255);

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
//  TODO: Add PWM adjustment code??
//  delay(5000);
}


void GreenLight(){
//  yellowState = false;
//  digitalWrite(RED_LED, LOW);
//  digitalWrite(GREEN_LED, HIGH);
//TODO: Add PWM adjustment code??
//  while(millis() - time_now > green_period && !gotInterrupt){
//    time_now = millis();
//  }
}

void setup() {
//  light_val = map(analogRead(PHOTO_PIN), 0, 1023, 0, 255);
//  dht.begin();
//  pinMode(BIKE_INT_PIN, INPUT_PULLUP);
  analogWrite(10,0);
  //Enable interrupt(s): PCINT0
  PCICR |= B00000001;
  PCMSK0 |= B00000001;
}

void loop() {
  //RED LIGHT ON
  gotInterrupt = false;

//  if(!gotInterrupt) RedLight();
//  if(waitingCars) GreenLight();
//  if(!gotInterrupt && waitingCars) YellowLight();

  if(gotInterrupt){
    //TODO: switch light to red so pedestrians can cross
//    if(yellowState){
//      RedLight();
//    }
//    else{
//      YellowLight();
//      RedLight();
//    }
//    testing interrupt
//    analogWrite(10, 255);
//    delay(1000);
  }

}
