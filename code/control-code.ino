#include <SharpIR.h>
#include <DHT20.h>
#include <util/delay.h>

#define PHOTO_PIN A0
#define IR_PIN A1
#define SOLAR_PIN 2
#define GRID_PIN 3
#define RED_LED_PIN 5
#define YELLOW_LED_PIN 9
#define GREEN_LED_PIN 6
#define WALK_LED_PIN 10
#define BIKE_INT_PIN 8
#define IR_SENSOR_MODEL 100500

const int ir_distance = 200;
int light_val;
int solar_val;
int brightness = 255;
unsigned long time_now;
int ir_val;
float humidity_val;
DHT20 dht;
SharpIR irSensor = SharpIR(IR_PIN,IR_SENSOR_MODEL);
volatile bool gotInterrupt = false;

const unsigned long red_delay = 10000;   //90000, 1:30 min
const unsigned long green_delay = 7000;
const unsigned long green_default_delay = 3000;
const unsigned long yellow_delay = 3000;

ISR (PCINT0_vect) 
{
  gotInterrupt = true;
} 

void RedLight(){
  analogWrite(RED_LED_PIN, brightness);
  ir_val = irSensor.distance();
  
  time_now = millis();
  bool bike_light_flag = true;
  while(ir_val > ir_distance){
    ir_val = irSensor.distance();
//    String ir_str = "~IR Distance: ";
//    Serial.println(ir_str+ir_val+" cm");
    if(millis()-time_now > red_delay/10 && bike_light_flag){
      analogWrite(WALK_LED_PIN, 255);
      bike_light_flag = false;
    }

    solar_val = analogRead(PHOTO_PIN);
    if(solar_val > 950){
      // Switch to solar
      digitalWrite(SOLAR_PIN, HIGH);
      digitalWrite(GRID_PIN, 0);
    }
    else{
      // Switch to grid
      digitalWrite(SOLAR_PIN, 0);
      digitalWrite(GRID_PIN, HIGH);
    }
  }

  int bike_flicker = 8;
  unsigned long int time_now2;
  bool flicker_flag = true;
  while(millis() - time_now < red_delay){
    if(millis()-time_now > red_delay/10 && bike_light_flag){
      analogWrite(WALK_LED_PIN, 255);
      bike_light_flag = false;
    }
    solar_val = analogRead(PHOTO_PIN);
//    String solar_str = "~Solar: ";
//    Serial.println(solar_str + solar_val);
    if(solar_val > 950){
      // Switch to solar
      digitalWrite(SOLAR_PIN, HIGH);
      digitalWrite(GRID_PIN, 0);
    }
    else{
      // Switch to grid
      digitalWrite(SOLAR_PIN, 0);
      digitalWrite(GRID_PIN, HIGH);
    }

    if(millis()-time_now > red_delay*2/3 && flicker_flag){
      time_now2 = millis();
      flicker_flag = false;
    }
    if(millis()-time_now > red_delay*2/3){
      if(millis()-time_now2 > (red_delay/3)/8){
        bike_flicker--;
        time_now2 = millis();
      }
      if(bike_flicker%2 == 0 || bike_flicker == 1){
        analogWrite(WALK_LED_PIN, 0);
      }
      else{
        analogWrite(WALK_LED_PIN, 255);
      }
    }
  }

  if(flicker_flag){
    time_now = millis();
    time_now2 = time_now;
    flicker_flag = false;
    while(millis() - time_now < red_delay/3){
      if(millis()-time_now2 > (red_delay/3)/8){
        bike_flicker--;
        time_now2 = millis();
      }
      if(bike_flicker%2 == 0 || bike_flicker == 1){
        analogWrite(WALK_LED_PIN, 0);
      }
      else{
        analogWrite(WALK_LED_PIN, 255);
      }

      solar_val = analogRead(PHOTO_PIN);
      if(solar_val > 950){
        // Switch to solar
        digitalWrite(SOLAR_PIN, HIGH);
        digitalWrite(GRID_PIN, 0);
      }
      else{
        // Switch to grid
        digitalWrite(SOLAR_PIN, 0);
        digitalWrite(GRID_PIN, HIGH);
      }
    }
  }
  analogWrite(RED_LED_PIN, 0);
  analogWrite(WALK_LED_PIN, 0);
}

void YellowLight(){
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
  int humidity_sensor_status = dht.read();
  switch (humidity_sensor_status)
  {
    case DHT20_OK:
      humidity_val = dht.getHumidity();
      break;
    default:
      humidity_val = 100;
      break;
  }

//------------------testing humidity sensor-------------
//  if(humidity_val > 60){
//    analogWrite(10, 255);
//  }
//  else{
//    analogWrite(10, 0);
//  }
//  delay(500);
//-------------------------------------------------------

  brightness = min(light_val+20, 255); 
  if(humidity_val > 80) brightness = 255;
  
//  String bright = "~Brightness: ";
//  Serial.println(bright+brightness);
//  String humidity_str = "~Humidity: ";
//  Serial.println(humidity_str+humidity_val); 
   
  time_now = millis();
  while(millis() - time_now < yellow_delay){
    solar_val = analogRead(PHOTO_PIN);
    if(solar_val > 950){
      // Switch to solar
      digitalWrite(SOLAR_PIN, HIGH);
      digitalWrite(GRID_PIN, 0);
    }
    else{
      // Switch to grid
      digitalWrite(SOLAR_PIN, 0);
      digitalWrite(GRID_PIN, HIGH);
    }
  }
  analogWrite(YELLOW_LED_PIN, 0);
}


void GreenLight(){
  PCMSK0 |= B00000001; //mask interrupts on pin 14: PCINT0 
  
  analogWrite(GREEN_LED_PIN, brightness);

  //Default green delay
  time_now = millis();
  while(millis() - time_now < green_default_delay){
    solar_val = analogRead(PHOTO_PIN);
    if(solar_val > 950){
      // Switch to solar
      digitalWrite(SOLAR_PIN, HIGH);
      digitalWrite(GRID_PIN, 0);
    }
    else{
      // Switch to grid
      digitalWrite(SOLAR_PIN, 0);
      digitalWrite(GRID_PIN, HIGH);
    }
  }
  
  time_now = millis();
  while(millis() - time_now < green_delay && !gotInterrupt){
    solar_val = analogRead(PHOTO_PIN);
    if(solar_val > 950){
      // Switch to solar
      digitalWrite(SOLAR_PIN, HIGH);
      digitalWrite(GRID_PIN, 0);
    }
    else{
      // Switch to grid
      digitalWrite(SOLAR_PIN, 0);
      digitalWrite(GRID_PIN, HIGH);
    }
  }

  analogWrite(GREEN_LED_PIN, 0);
  
  PCMSK0 &= B00000000; //unmask interrupts
}

void setup() {
  Serial.begin(19200);
  dht.begin();
  
  pinMode(WALK_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(SOLAR_PIN, OUTPUT);
  pinMode(GRID_PIN, OUTPUT);
  
  analogWrite(WALK_LED_PIN, 0);
  analogWrite(RED_LED_PIN, 0);
  analogWrite(YELLOW_LED_PIN, 0);
  analogWrite(GREEN_LED_PIN, 0);
  digitalWrite(SOLAR_PIN, 0);
  digitalWrite(GRID_PIN, HIGH);

  light_val = map(analogRead(PHOTO_PIN), 0, 1023, 0, 255);
  
  PCICR |= B00000001; //Enable interrupts on port B (PCINT0-PCINT7)
  PCMSK0 &= B00000000; //unmask interrupts on all pins
}

void loop() {
  gotInterrupt = false;

  RedLight();
  GreenLight();
  YellowLight();

}
