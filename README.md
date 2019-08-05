# NERF Ammo Counter
Arduino code and EAGLE schematics file for an ammo counter for NERF blasters.


## Features
* lets you choose between pre-defined mag sizes (12, 30, 6)
* counts down the available darts in the magazine
* resets counter on a reload (magazine change)


## Arduino compatibility
Developed for and tested with an Arduino Pro Mini (without header pins) or a clone thereof.


## Parts required
* 5V Arduino Pro Mini (or a clone) with FTDI programmer
* 0.96-inch SSD1306-compatible I2C OLED display
* some small-diameter wire (e.g. 0.14mm²)
* 3 10 kOhm resistors
* 3 push-button switches
* 1 toggle switch (optional)



## Installation into the blaster
Image:    [schematics](nerf_ammo_counter.png)

EAGLE schematics file:    [nerf_ammo_counter.sch](nerf_ammo_counter.sch)


The installation is completely up to you and depends on the actual blaster of your choice.

Basics steps:

* Connect the RAW and GND directly to the battery circuit of your blaster
* Place and wire the push-button switches according to their function:

   "firing" button has to be pressed when the trigger is depressed all the way  
   "reload" button has to be depressed when a magazine is taken out of the blaster  
   "select" button can be placed anywhere you're comfortable with  

* Mount the OLED display onto your blaster and wire it (e.g. cut a hole into the shell)




## Notes and tipps
Use a blaster with a decent amount of space, like a Stryfe, Rapidstrike or Hyperfire.

If enough space is available, use a piece of perfboard to share connections to ground and mains.


This project assumes that you have already modded the blaster to use a LiPo Battery (7.4V and 11.1V are both fine).
The normal Mignon batteries are to weak to power both the flywheels and the Arduino reliably.




## License
[MIT License](LICENSE)
