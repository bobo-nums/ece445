# Solar-Powered Traffic Light

Team Members:
- Colin Tarkowski (colinet2)
- Bowen Xiao (bowenx2)
- Richard Przybek (przybek2)

# Problem

Traffic lights are integral to our society, despite their relative lack of innovation over the years. The most significant change has been the switch from incandescent bulbs to LEDs in an attempt to reduce the power consumption of this necessary device. However, this has also led to an increase of light pollution due to the cooler, more intense light emitted by LEDs. They can cause extreme glare and pose a danger to drivers at night. Additionally, the issue of bicyclists and vehicles sharing the road can create many awkward or dangerous situations due to the lack of separation.

# Solution

We propose a solar-powered traffic light system that will solve the issues of drivers and bicyclists sharing the intersection and of light pollution, in addition to reducing consumption of traditional power in two ways. A pressure sensor located near the intersection, such as located upon a nearby curb, will detect whether there is a bicyclist present. Maybe a button instead? The system will be solar powered to minimize utility power utilized during the day. Connection to the grid will be necessary for operation at night or when solar conditions are suboptimal. At night, when light pollution is a significant issue, PWM circuitry will correspondingly dim the LED modules by limiting current. This not only reduces light pollution, but also lowers utility consumption at night.

# Solution Components

## Subsystem 1 - Power

The system will be powered with a solar panel and will include a buck/boost converter to regulate the voltage to 24V. The exact voltage of the panel will depend on what is available in the lab, ideally 24V. Solar power will be generated by ECEB solar panels (if possible) or a purchased module. For backup, we will utilize an AC/DC converter to step the 120VAC utility voltage down to 24VDC. We will also need DC/DC converters to 5V and 3.3V to power the microcontroller and sensors.

## Subsystem 2 - Control
This subsystem will include a microcontroller. It will take data from the pressure sensor (or other used for bicyclists), infrared sensor, and photodiode, process it, and change the traffic lights accordingly.

## Subsystem 3 - Traffic light system
This subsystem will require the aforementioned light modules, all of which can be acquired from a company called Leotek. Their website mentions samples and we hope to be able to utilize the following modules from them: 1x red, 1x yellow, and 3x green 10-28V LED traffic signal modules (see here).

- Additional 2 green modules will be for the bicycle and the walk sign
- If we are unable to acquire these modules, we can construct arrays of the desired LEDs that will operate at the same intended voltage of 24VDC. In this case, the bicycle and walk signs will be constructed with cutouts placed over the module that display the desired shape
- A pressure sensor will be utilized to detect when a bicyclist is at the intersection and an infrared sensor will detect whether a car is at the intersection and how many are present. Alternatively, we could use a camera system to run object detection algorithms on cars and bikes (we could accomplish this using an openMV chip, look into openVx applications, or as a last resort run openCV on a raspberry pi)

# Criterion For Success

A successful project will fulfill the following requirements:

- A standard traffic light (red, yellow, green), a walk light, and a bicycle light controlled on a timer with sensors that adjust the sequence and timing
- An infrared sensor will be utilized to detect when a vehicle is in a given area and the light will then turn green. Pedestrians will be able to press a button to trigger a walk sign shortly afterward
- In order to limit light pollution at night, PWM circuitry will be installed to ensure that the LED is dimmed when the ambient light is sufficiently dark. This will reduce light pollution while reducing the power consumed by the traffic light at night
- Connection to 120VAC grid power will be required to operate the system at night or during cloudy days. System should be able to switch smoothly between solar and grid power
- Will detect traffic flow and adjust timing of lights accordingly, in real time. Vehicle numbers will be detected by the infrared sensor and the timing of the traffic light will be altered autonomously to limit traffic congestion
- Be able to withstand typical weather conditions (waterproof, cold and heat resistant)
- OPTIONAL: Provide manual override to blinking red light for emergency situations
- OPTIONAL: Incorporate MPPT and develop software that will rotate the solar panel along a single access to maximize solar power consumption during the day. This will minimize the need for grid power around dawn and dusk

# NOTE
A system will only be developed for one of the four directions of the intersection, as the other three would simply require equivalent or complementary function. This will also reduce cost and help the project to stay within budget.