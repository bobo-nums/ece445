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

# Meeting with Gregg (3/22/22)
Today we all went to meet and talk to Gregg about our physical design. Our original plan was overly ambitious for Gregg so he said we would need to scale down a lot. The lights themselves are each almost a foot wide in diameter so the box for the lights would be atleast 4 ft tall. We decided that for the sake of our demonstration making just the box for the lights and housing our power and light boards inside it would be enough. A smaller box attached to the top of the traffic light would hold our MCU board and all the sensors that need to connect to it. 

I also made a rough draft of our code for our MCU board today. We do not have the board itself yet so I will have to figure out all the pin mappings once the board is put together. This is a very rough idea of how the code will be layed out, it will need to be revised heavily once the board is put together. See the first rough draft of our code in the figure below.

# Soldering MCU board (3/23/22)
The other day our first order of PCBs came in. I soldered together the whole MCU board today and did some continuity tests to make sure everything was connected correctly.

# Programming the MCU (3/26/22)
I went into the lab to begin programming the MCU board. Following Bowen's advice, I used the Arduino Mega as a programmer uploading the ArduinoISP onto it. I was fiddling around with this for a long time before realizing I had connected the RESET_PIN of the ISP incorrectly. Once this was fixed, I programmed the control board to run a basic LED blink program to make sure it was programmable. 

# Testing light and humidity sensors (3/27/22)
Today I went into lab to test the photoresistor sensors and the humidity sensors. I found a Arduino library to use with our humidity sensor that makes interfacing with it relatively easy. I got both sensors functioning properly and updated our code (see figure below). Programming the MCU board with the Arduino Mega poses a problem with getting serial data from the control board. For the time being I am testing with some LEDs and using PWM to write their brightness based on values we get from our sensors. This how the lights will be adjusted once they are attached to our full scale traffic light so it simulates our full system rather well.  

# Adding state machine and button interrupt (3/29/22)
I set up a more robust state machine machine in our code today. Making each light an individual state as in our original control flow diagram. I also began implementing the pedestrian/biker button interrupt. The button should be able to make an interrupt in any state and be handled appropriately. There seems to be an issue with using the delay() function from arduino libraries. Although the interrupt is happening in within the delay function there is no way to exit from the delay. There are also time where it seems like the button interrupts are locking and the interrupt does not get handled at all. I will need to find a more convenient way to handle interrupts, in this current way they are not reliable.

# Testing optoisolators and power monitor on power board (3/31/22)
I soldered together the power monitor, optoisolators, and jumpers on the power board to try and test the power monitor today. It was somewhat awkward to test the optoisolators there is no pins to attach wires to. I soldered wires to the ends of resistors and other PCB pads in an attempt to test. I ended up trying to power the board from a microcontroller and use a external power supply on the other side of the collector emittor side of the optoisolator to try and test the IC. It seemed like this did not work at all the optoisolator was not switching at all when I pulled the MCU pin high or low.

# Testing optoisolator attempt #2 (4/1/22)
I went into the lab again to test the optoisolators. I powered the power board from the MCU again. This time I tried connecting the MCU pins and programming the microcontroller to raise or lower the pins. This is how it will be connected later in our full design so this should have worked as expected. I went to attach the external power supply on the collector emittor side again. The first thing I noticed was there did not seem to be any difference when I raised or lowered the MCU pins. Then I noticed the collector emitter side of the optoisolator was drawing a lot of current, nearly 2A. There was clearly a short somewhere but I was not sure where. 

# Fixing button interrupt and testing IR sensor (4/4/22)
I tested the IR sensor today and fixed our button intterupt. The found a arduino library that goes with our IR sensor and makes communicating with it much easier. I used a ruler and a test LED to see whether the distance was being accurately read from the sensor. At first the distances seemed to be very short and not accurate. Bowen suggested I use an external power supply for the IR sensor, I did this and it seemed to fix the issue somewhat. The sensor could read much further distance, although the background of the lab is rather noisy with a lot of different colors. This could make it harder to get accurate readings at much longer distances.

I also fixed our button interrupt issue today and simplified the state machine greatly. First I found millis() is a much more reliable function for getting accurate timing and allowing button interrupts to occur at any time. Although, later I realized that button interrupts really only need to happen during a green light phase when a pedestrian is trying to cross but traffic still has a green light. Rather than having the system be always interruptable I changed it so button interrupts are only masked in the green light phase. The button interrupt is fully functional now and works very reliably for pedestrians, switching to yellow-red sequence when the button is pressed.

The code in its current state should be fully operational (except the power monitor) on our full scale system. Once everything is assembled we will just need to test our full system and tune parameters from our sensors to adjust the brightness of our lights and the timing of the light sequence.

# Testing optoisolator attempt #3 (4/8/22)
Looking for the short on our power board PCB again today. After talking to Bowen some more about the power board I found that the jumpers were causing the short. I ended up removing two of four jumpers, this is ok because they are not entirely necessary. The jumpers are used to dictate the I2C address of the power monitor, but GND GND is one of the available configurations. I got rid of the short and went to test again. This time the collector emitter side seemed to draw an appropriate amount of current of a few mA, but the MCU pins on the anode cathode side did not seem to switch it on or off. After talking to Colin and looking deeper into the datasheet it seems like the optoisolator might be reseting too quickly to be able to tell. Colin did some testing on his own and says it should be working. We will go with this assumption and test the power monitor.

# Soldering light board v2 (4/14/22)
I soldered together our version 2 of the light board PCB and tested it with our microcontroller and hooking it up to our big lights. I simply had one of the big lights blink and this seemed to work correctly. Bowen pointed out that I soldered some solder jumpers unnecessarily. I will have to go remove these and test once again to see if the optoisolators on the light board are working correctly.
