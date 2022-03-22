#include <Wire.h>
#define PHOTO_PIN 9
#define IR_PIN 10
#define SDA 0
#define SCL 1
#define RED_LED 3
#define YELLOW_LED 4
#define GREEN_LED 5

cont int ir_distance = 12 //12-18 ft?
int light_val;
int ir_val;

void setup() {
  // put your setup code here, to run once:
  light_val = analogRead();
  Serial.begin(9600);
}

void loop() {
  //Red light turns on
  digitalWrite(RED_LED, HIGH);
  delay(90000);
  ir_val = analogRead(IR_PIN);
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

  light_val = analogRead(PHOTO_PIN);
  //TODO: Read humidity sensor value through i2c

  delay(5000);
}
