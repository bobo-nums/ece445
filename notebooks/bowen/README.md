# Bowen Worklog
## 2/7/22 - Work on proposal
We met and worked on our project proposal. We found some components that could work for our sensors and researched the difference between a photodiode and light dependent resistor. It seems that a light dependent resistor is cheaper, has a slower response, and is tuned to the visible spectrum. Since weather changes slowly, an LDR might be a bettery choice than a photodiode. 

- SEN-18364 humidity and temperature sensor
    - 2.2V - 5.5V
    - I2C communication
    - op. temp: -40&deg;C to 80&deg;C
- GP2Y0A21YK0F IR sensor
    - 4.5V - 5.5V
    - 30mA operating current
    - op. temp: -10&deg;C to 60&deg;C

We also researched how to smoothly switch between two different power sources and found something called a power mux. However, none of the components could support a 24V input, so we might need to find something else, or switch to 12V LEDs. 

## 2/8/22 - First TA meeting
Today, we met with Qingyu and went over our proposal. He said we were progressing nicely, but he did have some comments. He advised us to:
- figure out how to demonstrate our final product
- add numbers and details to the high level requirements
- list specific communication protocols on our block diagram
- talk to another TA or professor about our power electronics questions

We were unsure if the 24V input switching was possible between the solar panel and grid power, so we will need to talk to someone with more experience in that field.

## 2/9/22 - Talk to TA
I went to Stasiu's office hours and asked him about the power switching system. If we used a voltage less than 24V, we could use a power mux. If we want to keep 24V, we might be able to create a switching network with solid state relays because of their fast switching speed, diodes to prevent reverse current flow, and some large capacitors to minimize volage transients.

## 2/14/22 - Picked out some components
started kicad stuff, picked out some componentsn...