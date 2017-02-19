The project implements the learning in firmware and different concepts learnt in the courses such as IOT and ESE. The project solves the high risk of car accidents when the car is at a high speed and suddenly decelerates due to an obstacle or misjudgement on the part of the driver. In case of such a case, the services get an alert in case of an accident. Also, it continuously monitors the machines for temperature changes which is supplied to the fire brigade if the car starts to catch a fire and the driver to alert them of sudden temperature elevations in the machinery. Negative temperatures can also be monitored. Thus, the driver can turn off his machine in case of elevated temperatures. Another added specification is the use of an ambient light sensor for automatic light control.
Devices Used:

-Leopard Gecko EFM32LG acting as a sensor hub:
  Temperature sensor used with ADC and DMA
  Low Energy UART and I2C
  LESENSE withCapacitive touch sensor which turns off the system when not required
   Managing different energy modes from EM0-EM3 thus saving energy
- ATMEL SAMB11 acting as a BLE master for radio connection.
- MMA8452Q 3-axis accelerometer
-TSL2561 ambient light sensor for precise value of ambient light and control
- ATMEL SMART APP acting as receiver and slave

Additional concepts involved:
-Load Power management
-Managing Energy modes
-Modularity
-Testability
-Software abstraction
-Function pointers
-inline functions
-Robustness
-Efficiency
-Structure
-Enumerations
-Preprocessor macros
-Interrupts
-Communication and logging
-Critical sections
-Version control
-events
-State machines
-DMA and ADC
