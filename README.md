Plush in the Box.

I created this little program for a game that entertains children a lot and built it with 3 servo motors, a switch, and an ESP8266.

Game explanation:
The game is a cubic box in which there is a small character. On the front of the box, halfway up on the left, there is a toggle switch. The switch is always oriented downwards. When children lift the switch, the little creature inside the box lifts the lid with its head and extends its arm to the left to bring down the switch. To give the impression of a living being, the program reacts randomly to lift the head, move the arm, or turn the head. The box can open only once or several times before the arm comes out and lowers the switch again. The plushie can, for example, open the lid, turn the head in both directions several times, then close the box before reopening it and quickly bringing down the switch.

Assembly explanation:
In the box, there is only the head and arm of the plushie. The arm is in the shape of a half-circle. The arm is mounted on a servo motor that rotates it to lower the switch when coming out of the box. The servo motor of the arm is glued to the left inner face of the box and rotates on a vertical axis.

Another servo motor is used to open and close the lid of the box. It also serves to raise and lower the head. The servo motor that opens the box and lifts the head is glued to the right inner face of the box and rotates on a vertical axis. I attached a rod that lifts the lid on the servo motor. The rod rotates on the vertical axis of the motor. Another rod is attached to the same motor with a bracket. The second rod is therefore horizontal at the bottom of the box.

On the rod at the bottom of the box, which rises when the servo motor on the right face rotates, another servo motor is attached. This third servo motor rotates with a horizontal axis. On this third servo motor, the head of the plushie is attached.

Finally, inside the box, fixed on the inner front face is a double diode that lights up when the box opens.


## Power Supply:
For the power supply, I wanted to avoid dependence on an external source such as a transformer. Therefore, in the box, I used 3 rechargeable AA batteries of 1.5 V each, connected in series, providing me with a voltage of 4.5 V.

I connected the adapter of the Semoic ESP8266 Serial ESP-01 Wi-Fi 3.3V 5V module. This voltage regulator then supplies a stable 3.3 V to the ESP8266. The servo motors are directly connected to their +5 V pin, and the GND is linked to the battery terminals. Finally, pins 12, 13, and 14 are connected to the servo motors, serving as outputs for the lid, arm, and head, respectively. They are connected to the "signal" pin of the servo motors.

Pin 11 is linked to the switch as input, and pin 15 is connected to the diodes. The diodes are powered by the 3.3 V output of the ESP8266 and connected to the GND of the ESP8266.

Have fun!!
