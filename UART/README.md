This project first starts with basic UART transmission and reception for a FRDM-KL25z board on the Kinetis Development Studio.
A logger function is implemented for calling the UART transmit function depending on what to transmit.
Later, we make a circular buffer for the implementation. The buffer size can be variable and has a wrapping functionality.
Then we use the circular buffer via the logger.
We also change the colors of the on-board LEDS and control their intensities by UART messages.
In the end, we make a timer profiler which calculates the time taken by every function to execute. Here we calculate times of memory and data functions written in the previous project i.e. MAKEFILE. Also we calculate the timing of the logger function specified above.
Also, we make a timer profile in the BEAGLEBONE platform.
The code is modular with various sub-sections and only an upper level main code available to the user.
