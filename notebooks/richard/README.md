# Project Proposal Meeting (2/7/22)
The goal of this session was to meet and discuss the requirements of our traffic light system and how everything would connect generally. Tomorrow we are meeting with our TA for the first time and we will get their opinion on what we come up with today. Prior to meeting I created the intial version of our visual aid diagram (see figure 1). After discussing the subsystems and components of our system I created the first version of our block diagram (see figure 2). There is missing details which will likely need to be added in the future (communication protocols between the sensors and the MCU, etc.). We briefly talked about parts we could use, we will make a more definitive list after ironing out some finer details.  

![Visual Aid](https://github.com/bobo-nums/ece445/blob/main/notebooks/richard/visual%20aid.PNG)
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
I added a figures for the main control flow of our microcontroller and all the tables in the cost analysis section. We wrote up the rest of the requirements and verifications for all the subsystems, completing the design doc. 
