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
We discussed power protection circuitry and implementing the switching network with either [LTC4357s](https://www.analog.com/media/en/technical-documentation/data-sheets/4357fd.pdf) or [LTC4359s](https://www.analog.com/media/en/technical-documentation/data-sheets/ltc4359.pdf). Both ICs provide similar functionality in terms of protection, but the LTC4359 has a shutdown pin which we can control using our microcontroller. We want to use an ATmega328, but they are out of stock everywhere. We might try to take one from an Arduino. I also worked on the KiCad schematic and mostly completed the microcontroller part. I added a 16MHz crystal oscillator, AVR programmer, power LED indicator, and a reset button.

![mcu](mcu.png)

## 2/15/22 - Weekly TA meeting
We met with our TA and he went over some concerns that he had. If the humidity sensor for some reason did not work in adverse weather conditions, we would have a manual override to change the light brightness to maximum. We clarified our design for the switching network and mentioned that we plan to use the LTC4359 to provide circuit protection and facilitate switching. Additionally, a current/voltage sense was needed to monitor the solar panel's output power. In order to monitor solar power when it is disconnected, we wanted to have a power resistor dissipating the excess power as heat. I worked on the 3.3V and 5V buck converters and chose components for them. 

![buck](buck.png)

## 2/19/22 - Work on schematic/simulations
I used LTspice to create a simulation of our 3.3V and 5V buck converters as well as the switching network using the LTC4359 ICs. We wanted to verify that our design could theoretically switch between solar and grid power supplies while minimizing voltage transients and switching time. The reference schematic was taken from the [LTC4359's datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ltc4359.pdf) and modified to fit  our voltage and current requirements (3A at 24V). 
![sim](switching_sim.png)
The two figures below show the voltage output and shutdown signals respectively. We can see that even when both outputs are off for 0.5ms, the voltage does not drop below around 23.89V, which fulfills our requirement. 
![sim_v](voltage.png)
![sim_shdn](shdn.png)

## 2/22/22 - Design document check
We had our design document check meeting today with Prof. Shao. She suggested we put more detail (power/data lines) into our block diagram, include more quantitative requirements & verifications, and include power drawn by sensors. We also determined that the switching network exceeded voltage transient requirements when we added a dummy load, so we will need to fix it.

## 2/28/22 - Power board PCB
I finished creating the schematic for the power board, which contains the 3.3V and 5V buck, 24V sepic converter, and the switching network. 
![pschem](power_board_schematic.png)
I also laid out the PCB. I tried to keep all systems together and ensure thick traces/copper pours when dealing with high current (anything greater than 1A).
![ppcb](power_board_pcb.png)

## 3/1/22 - Design document presentation/PCB board check
Today we presented our design document and received a few criticisms. The first bullet point of our high level requirements should include the power cost estimate of the entire system and compare it with a normal traffic light system to see how much energy/money we expect to save. There were also minor comments like changing the colors/background of some figures to make it more legible. 

We only finished the power board for the PCB board check. Our board was over the 100mm x 100mm size, so I needed to move the 3.3V and 5V buck converters onto the MCU board. This is the new power board.
![ppcb2](power_board_pcb2.png)

For the light board, we will need to perform some tests on the lights to determine if we need a current limiting resistor. I couldn't find anything in the datasheet.