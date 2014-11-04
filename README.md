Arducar
=======
A simple robot car made with Arduino. 

This project was carried out during an [ITSAS](http://ehu.es/itsas) workshop in the [Facultad de Informática de San Sebastián](http://www.ehu.es/informatika-fakultatea).  

Thanks to all the participants and the rest of the people who made this possible.  

![Arducar photo](arducar01_red.png)

Short description + Components
------------------------------
This autonomous robot car follows a straight path. Once set on a surface the robot meassures its deviation from the earth's magnetic north and tries to stick to that deviation when moving forwards (allowing a small error).

[Video: Preliminary version with remote control tablet Android](https://www.facebook.com/video.php?v=646924202010643&set=vb.631804706855926&type=2&theater)

The car was built using the following core elements: an arduino UNO (Rev.3) board, a [dfrobot motor shield](http://www.dfrobot.com/index.php?route=product/product&product_id=69) and a HMC5883L magnetometer.

This robot is powered by 8 AA (1'5V) batteries. 4 of them power the motors, through the motor shield, and the other 4 power the arduino UNO board.

Schematic
---------
![Schematic](arducar_schematic.png)

The schematic source is the arducar_schematic.fzz file. It can be opened with the [fritzing environment](http://fritzing.org/home/).

License
-------
This code is in public domain. 
A link to the this project would be appreciated in case you publish something based on the code or schematics herein available.
