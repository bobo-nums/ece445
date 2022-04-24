# Project Proposal Meeting (2/7/22)
The goal of this session was to meet and discuss the requirements of our traffic light system and how everything would connect generally. Tomorrow we are meeting with our TA for the first time and we will get their opinion on what we come up with today. Prior to meeting I created the intial version of our visual aid diagram (see figure 1). After discussing the subsystems and components of our system I created the first version of our block diagram (see figure 2). There is missing details which will likely need to be added in the future (communication protocols between the sensors and the MCU, etc.). We briefly talked about parts we could use, we will make a more definitive list after ironing out some finer details.  

![Visual Aid](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/visual%20aid.PNG) <br>
![Block Diagram V1](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/block_diagramV1.PNG)


# First TA Meeting (2/8/22)
Today we had our first meeting with our TA, Qingyu. We discussed the project proposal and what our design looks like so far for the project. 
The main points Qingyu made were that we should think about how we will demonstrate our project considering the solar panel will need to be in the sun. Qingyu also urged
us to get together a parts list and design our pcb as soon as possible so we can order them and ensure we have everything put together in time to demo. We also took a look at
the block diagram and Qingyu confirmed it was lacking in detail and we will need to update it in the future.

# Meeting to discuss ideas and pick parts (2/12/22)
In this meeting we tried to pick out most of our parts. We decided we could use the ATMEGA328 MCU since we already have some in our possession and it would meet the demands of our project. I started formatting the design document for us to fill in as we figured out more of our project. We discussed different options for how we would handle the switching network, we decided we needed to talk to TA's to get a better idea of what to do. We found some components such as a power mux and a power ORing controller. After talking to some TA's we will decide which is the best option.

# Second TA meeting (2/15/22)
We had our second TA meeting today and went over some finer details. In particular for our power system how we would be switching between the grid power and solar panel. Our plan as of right now is to use a large resistor tied to GND to take voltage readings from the solar panel and be able to tell if there is sufficient power to use it. This will draw a little bit of power that goes to waste, ideally we would be able to feed this energy back into the grid but this is beyond the scope of our current project.

# Writing up design document (2/20/22)
I added a figures for the main control flow of our microcontroller and all the tables in the cost analysis section. We wrote up the rest of the requirements and verifications for all the subsystems, completing the first version of our design doc. 

![Control Flow V1](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/control_flow_v1.PNG) <br>
![Labor Cost Table](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/labor%20cost%20table.PNG) <br>
![Parts Cost Table](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/parts%20cost%20table.PNG) <br>
![Schedule Table](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/schedule%20table.PNG)

# Contacting Leotek for light sample (2/21/22)
Today I received word back from Leotek about getting some sample traffic lights shipped to us. They were able to get us all the samples we requested: 1 green light 24VDC, 1 yellow light 24VDC, 1 red light 24VDC, and 1 bike light 120 VAC. They should ship whithin the next two weeks.

# Testing Traffic lights (3/2/22)
The traffic lights came in a few days ago. Bowen and I went into the lab to test them and see how much current they draw. At 24VDC the red, yellow, and green lights draw 0.23A, 0.21A, and 0.31A respectively.

# Contacting Gregg (3/5/22)
I got into contact with Gregg about coming into the machine shop and starting to work on our physical design for the project. In the email I sent him I made a rough sketch of what we were thinking about doing for the dimensions of our traffic light (see the figure below). It would have a pole that the traffic light itself attaches too. Inside the traffic light we would be housing most of our sensors and microcontroller board. On the side of the traffic light we would have another box to house our power board. Ideally we would also have the traffic light weather-proofed but this may be out of the capabilities or budget of the machine shop.

![Dimensions sketch](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/dimensions%20sketch.PNG) 

# Meeting with Gregg (3/8/22)
Today we all went to meet and talk to Gregg about our physical design. Our original plan was overly ambitious for Gregg so he said we would need to scale down a lot. The lights themselves are each almost a foot wide in diameter so the box for the lights would be atleast 4 ft tall. We decided that for the sake of our demonstration making just the box for the lights and housing our power and light boards inside it would be enough. A smaller box attached to the top of the traffic light would hold our MCU board and all the sensors that need to connect to it. 

# Rough draft of control code (3/22/22)
I made a rough draft of our code for our MCU board today. We do not have the board itself yet so I will have to figure out all the pin mappings once the board is put together. This is a very rough idea of how the code will be layed out, it will need to be revised heavily once the board is put together. See the first rough draft of our code in the figure below. Gregg also finished our physical design recently, attached below is photo of our finished physical design.
```
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
```

![Physical Design Photo](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/Physical_design_picture.jpeg)

# Soldering MCU board (3/23/22)
The other day our first order of PCBs came in. I soldered together the whole MCU board today and did some continuity tests to make sure everything was connected correctly.

# Programming the MCU (3/26/22)
I went into the lab to begin programming the MCU board. Following Bowen's advice, I used the Arduino Mega as a programmer uploading the ArduinoISP onto it. I was fiddling around with this for a long time before realizing I had connected the RESET_PIN of the ISP incorrectly. Once this was fixed, I programmed the control board to run a basic LED blink program to make sure it was programmable. Our 

# Testing light and humidity sensors (3/27/22)
Today I went into lab to test the photoresistor sensors and the humidity sensors. I found a Arduino library to use with our humidity sensor that makes interfacing with it relatively easy. I got both sensors functioning properly and updated our code (see figure below). Programming the MCU board with the Arduino Mega poses a problem with getting serial data from the control board. For the time being I am testing with some LEDs and using PWM to write their brightness based on values we get from our sensors. This how the lights will be adjusted once they are attached to our full scale traffic light so it simulates our full system rather well.
```
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
```
# Adding state machine and button interrupt (3/29/22)
I set up a more robust state machine machine in our code today. Making each light an individual state as in our original control flow diagram. I also began implementing the pedestrian/biker button interrupt. The button should be able to make an interrupt in any state and be handled appropriately. There seems to be an issue with using the delay() function from arduino libraries. Although the interrupt is happening in within the delay function there is no way to exit from the delay. There are also time where it seems like the button interrupts are locking and the interrupt does not get handled at all. I will need to find a more convenient way to handle interrupts, in this current way they are not reliable.
```
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
```
# Testing optoisolators and power monitor on power board (3/31/22)
I soldered together the power monitor, optoisolators, and jumpers on the power board to try and test the power monitor today. It was somewhat awkward to test the optoisolators there is no pins to attach wires to. I soldered wires to the ends of resistors and other PCB pads in an attempt to test. I ended up trying to power the board from a microcontroller and use a external power supply on the other side of the collector emittor side of the optoisolator to try and test the IC. It seemed like this did not work at all the optoisolator was not switching at all when I pulled the MCU pin high or low.

# Testing optoisolator attempt #2 (4/1/22)
I went into the lab again to test the optoisolators. I powered the power board from the MCU again. This time I tried connecting the MCU pins and programming the microcontroller to raise or lower the pins. This is how it will be connected later in our full design so this should have worked as expected. I went to attach the external power supply on the collector emittor side again. The first thing I noticed was there did not seem to be any difference when I raised or lowered the MCU pins. Then I noticed the collector emitter side of the optoisolator was drawing a lot of current, nearly 2A. There was clearly a short somewhere but I was not sure where. 

# Fixing button interrupt and testing IR sensor (4/4/22)
I tested the IR sensor today and fixed our button intterupt. The found a arduino library that goes with our IR sensor and makes communicating with it much easier. I used a ruler and a test LED to see whether the distance was being accurately read from the sensor. At first the distances seemed to be very short and not accurate. Bowen suggested I use an external power supply for the IR sensor, I did this and it seemed to fix the issue somewhat. The sensor could read much further distance, although the background of the lab is rather noisy with a lot of different colors. This could make it harder to get accurate readings at much longer distances.

I also fixed our button interrupt issue today and simplified the state machine greatly. First I found millis() is a much more reliable function for getting accurate timing and allowing button interrupts to occur at any time. Although, later I realized that button interrupts really only need to happen during a green light phase when a pedestrian is trying to cross but traffic still has a green light. Rather than having the system be always interruptable I changed it so button interrupts are only masked in the green light phase. The button interrupt is fully functional now and works very reliably for pedestrians, switching to yellow-red sequence when the button is pressed. There is a picture of my test setup below with all the sensors connected.

The code in its current state should be fully operational (except the power monitor) on our full scale system. Once everything is assembled we will just need to test our full system and tune parameters from our sensors to adjust the brightness of our lights and the timing of the light sequence.
```
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
```

![Test Sensors](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/MCU_sensor_test.jpeg)

# Testing optoisolator attempt #3 (4/8/22)
Looking for the short on our power board PCB again today. After talking to Bowen some more about the power board I found that the jumpers were causing the short. I ended up removing two of four jumpers, this is ok because they are not entirely necessary. The jumpers are used to dictate the I2C address of the power monitor, but GND GND is one of the available configurations. I got rid of the short and went to test again. This time the collector emitter side seemed to draw an appropriate amount of current of a few mA, but the MCU pins on the anode cathode side did not seem to switch it on or off. After talking to Colin and looking deeper into the datasheet it seems like the optoisolator might be reseting too quickly to be able to tell. Colin did some testing on his own and says it should be working. We will go with this assumption and test the power monitor.

# Soldering light board v2 (4/14/22)
Our second round of PCB orders came in. I soldered together our version 2 of the light board PCB and tested it with our microcontroller and hooking it up to our big lights. I simply had one of the big lights blink and this seemed to work correctly. Bowen pointed out that I soldered some solder jumpers unnecessarily. I will have to go remove these and test once again to see if the optoisolators on the light board are working correctly.

# Getting serial data (4/19/22)
I found a work around for getting serial data from our mcu board through our ArduinoISP by modifying the ISP code. We could now collect data from all our sensors on the MCU board and tune sensor values. 

# Testing power monitor (4/20/22)
Bowen and I attempted to debug the power monitor and restested the optoisolators. We attmepted to do an i2c scan but no addressable devices were found. The i2c communication did not seem to work with the power monitor. We tried to bypass the optoisolators and connect SDA and SCL lines directly to the power monitor. This did not work either. After 5 hours of exhaustive testing we could not get communication to work with the power monitor. We went on to assemble the rest of our system. We came up with a plan B, we would use the photoresistor to tell us when there is enough light to operate on solar power. 

# Assembling everything and tuning (4/23/22)
Today we assembled our system entirely. I tuned the sensor values making the IR sensor detecting distances of 4-7 feet. I tuned our PWM values so our light remains visible at a distance while it is dimmed in night conditions and added a flicker effect to our bike light to give bikers a warning when the light is about to change.

(add video)

