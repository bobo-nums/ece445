# Colin Worklog

[TOC]

# 2022-02-07 - Meeting for Project Proposal
We met to discuss the inner workings of the project proposal.  Specific attention was paid to the parts (i.e. sensors) and the block diagram, which Richard and I developed.  Progress is still needed for both of these components before finalizing the proposal by Thursday, 02/10.

# 2022-02-08 - First Meeting with Qingyu
Today we met with Qingyu for the first time to discuss where our project is at right now.  We will shift our focus to a few key details as we finish the project proposal:
1. Planning how we will demonstrate the various functions of the traffic light
2. Adding details to block diagram (i.e. sensor protocols and specific parts)
3. Contacting TA Evan Widloski and Professors Schuh and Banerjee about the power switching component of our design
    * LTC4412 - OR'ing of multiple power sources ([datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/4412fb.pdf "LTC4412"))
    * Power MUX
    * Possibility of manual switch (worst case scenario)

I will email the people listed above for advice about which strategy to use, while in the search of new ideas.

# 2022-02-10 - Finishing the Proposal
Today we were able to put the finishing touches on the project proposal by clarifying the high-level and subsystem requirements.  I also placed a sample order for the LTC4357 and LTC4359 chips from Analog Devices.  The chips will be delivered soon and a pair of one device (likely LTC4359) will be used to manage the switching between the solar and grid power.  They will control which source is used by driving an external pair of complementary MOSFETs.  These MOSFETs still need to be chosen.  Refer to the following datasheets: [LTC4357](https://www.analog.com/media/en/technical-documentation/data-sheets/4357fd.pdf "LTC4357") and [LTC4359](https://www.analog.com/media/en/technical-documentation/data-sheets/ltc4359.pdf "LTC4359")

# 2022-02-14 - Selecting More Components
We met today to discuss some of the finer details of the project that had not been ironed out yet.  We have now decided on the LTC4359 to aid in the switching of the two power sources, but are also exploring options about how to monitor the available solar power when it has already been switched off.  Our most likely option is a "dummy" load consisting of a simple power resistor but we will discuss this with out TA tomorrow.

# 2022-02-15 - Weekly TA Meeting
