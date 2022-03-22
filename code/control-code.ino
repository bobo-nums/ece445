#include <DHT20.h>
#define PHOTO_PIN 9
#define IR_PIN 10
#define RED_LED 3
#define YELLOW_LED 4
#define GREEN_LED 5

cont int ir_distance = 8 //8 ft?
int light_val;
int ir_val;
float humidity_val;

void setup() {
  light_val = analogRead();
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  //Red light turns on
  digitalWrite(RED_LED, HIGH);
  delay(90000);
  //TODO: Add IR sensor reading
//   ir_val = analogRead(IR_PIN);
  while(ir_val > ir_distance){
    ir_val = analogRead(IR_PIN);
  }

  //Green light turns on
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  //TODO: Add PWM adjustment code
  delay(90000);

  //Yellow light turns on
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  
  //Take photoresistor reading
  light_val = analogRead(PHOTO_PIN);
  
  //Take humidity reading
  int humidity_sensor_status = dht.read();
  switch (humidity_sensor_status)
  {
    case DHT20_OK:
//       Serial.print("OK,\t");
      humidity_val = dht.getHumidity();
      break;
    default:
      Serial.print("Unknown error,\t");
      humidity_val = 100;
      break;
  }

  delay(5000);
}
