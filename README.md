Plush in the Box.

I created this little program for a game that entertains children a lot and built it with 3 servo motors, a switch, and an ESP8266.

Game explanation:
The game is a cubic box in which there is a small character. On the front of the box, halfway up on the left, there is a toggle switch. The switch is always oriented downwards. When children lift the switch, the little creature inside the box lifts the lid with its head and extends its arm to the left to bring down the switch. To give the impression of a living being, the program reacts randomly to lift the head, move the arm, or turn the head. The box can open only once or several times before the arm comes out and lowers the switch again. The plushie can, for example, open the lid, turn the head in both directions several times, then close the box before reopening it and quickly bringing down the switch.

Assembly explanation:
In the box, there is only the head and arm of the plushie. The arm is in the shape of a half-circle. The arm is mounted on a servo motor that rotates it to lower the switch when coming out of the box. The servo motor of the arm is glued to the left inner face of the box and rotates on a vertical axis.

Another servo motor is used to open and close the lid of the box. It also serves to raise and lower the head. The servo motor that opens the box and lifts the head is glued to the right inner face of the box and rotates on a vertical axis. I attached a rod that lifts the lid on the servo motor. The rod rotates on the vertical axis of the motor. Another rod is attached to the same motor with a bracket. The second rod is therefore horizontal at the bottom of the box.

On the rod at the bottom of the box, which rises when the servo motor on the right face rotates, another servo motor is attached. This third servo motor rotates with a horizontal axis. On this third servo motor, the head of the plushie is attached.

Finally, inside the box, fixed on the inner front face is a double diode that lights up when the box opens.

In the box, there are 3 rechargeable 1.5-volt batteries, connected in series, giving me 4.5 volts. Between the batteries and the ESP8266, which must be powered with 3.3 volts, I have installed the Semoic ESP8266 Serial Wireless Module Adapter ESP-01 Wi-Fi 3.3V 5V. This voltage regulator can take up to 5 volts as input and deliver 3.3 volts to the ESP8266. You can also use a phone charger that provides 5 volts instead of batteries if you prefer.

Have fun!!


FYI:

. Variables and constants in RAM (global, static), used 28168 / 80192 bytes (35%)
║   SEGMENT  BYTES    DESCRIPTION
╠══ DATA     1520     initialized variables
╠══ RODATA   928      constants       
╚══ BSS      25720    zeroed variables

. Instruction RAM (IRAM_ATTR, ICACHE_RAM_ATTR), used 60647 / 65536 bytes (92%)
║   SEGMENT  BYTES    DESCRIPTION
╠══ ICACHE   32768    reserved space for flash instruction cache
╚══ IRAM     27879    code in IRAM    

. Code in flash (default, ICACHE_FLASH_ATTR), used 234404 / 1048576 bytes (22%)
║   SEGMENT  BYTES    DESCRIPTION
╚══ IROM     234404   code in flash
