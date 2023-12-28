#include <Servo.h>
// Define pin constants
const int switchPin    = 12;  // Pin for the switch
const int servoLidPin  = 13;  // Pin for the lid servo motor
const int servoArmPin  = 14;  // Pin for the arm servo motor
const int servoHeadPin = 15;  // Pin for the head servo motor
const int diodePin     = 16;  // Pin for the LED


Servo servoLid;             // Servo for the Lid
Servo servoArm;             // Servo for the Arm
Servo servoHead;            // Servo for the Head

// Define angle constants
const int angleMinimumAmplitude  =   0;   // Minimum amplitude of the arm servo motor 
const int angleMaximumAmplitude  = 120;   // Maximum amplitude of the arm servo motor
const int openingLidAngle        =   0;   // Minimum lid opening position to extend the arm
const int maxOpeningMid          =  51;   // Maximum opening angle of the lid.
const int minOpeningLid          =  15;   // Minimum opening angle of the lid.
const int closureLid             =   0;   // Angle at which the lid is considered closed
const int leftHeadAngle          =  40;   // Maximum left angle to turn the head
const int centerHeadAngle        =  90;   // Centered head looking straight
const int rightHeadAngle         = 140;   // Maximum right angle to turn the head

bool isSwoff                     = false; // Indicates whether the arm has lowered the switch or not

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(diodePin, OUTPUT);
  servoLid.attach(servoLidPin);
  servoArm.attach(servoArmPin);
  servoHead.attach(servoHeadPin);
}

void loop() {
    // Check the state of the switch
    if (digitalRead(switchPin) == HIGH) {
        digitalWrite(diodePin, HIGH);       // Turn on the LED
        isSwoff = false;
        randomBehavior();
    }
}

void moveServo(Servo& servo, int currentPosition, int finalPosition, int speed) {
    
    int newPosition = 0;
    int elapsedAnimation = 0;

    if (finalPosition < currentPosition)
        speed = speed * -1; // Make speed negative if the current position is greater than the final position

    while (servo.read() != finalPosition) {

        newPosition = servo.read() + speed;

        // Limit overflows
        newPosition = constrain(currentPosition + speed, finalPosition, currentPosition);
        servo.write(newPosition);
        delay(10); // Wait for the servo motor to finish moving
        elapsedAnimation += 10;
    }
}

void moveLid() {
    // Code to lift the lid with the servo motor
    if (servoLid.read() > closureLid) // Lid already open, so close it
        moveServo(servoLid, servoLid.read(), closureLid, random(5, 50)); // Lift the lid to the specified angle
    else
        moveServo(servoLid, servoLid.read(), random(minOpeningLid, maxOpeningMid), random(5, 50)); // Lift the lid to the specified angle
}

void headSpin() {
    // Code to randomly turn the head
    int animationTime = random(0, 5001); // Random animation time between 0 and 5000 ms
    int headAngle   = 0;                 // Final head position
    int movement   = 0;                  // Determines whether the head should move left, right, or stay still
    int movementSpeed   = 0;             // Head movement speed
  //  int currentPosition = 0;           // Current head position

    while (animationTime > 0) {

        // Determine if the head should move left, right, or stay still
        movement = random(-1, 2);        // -1 for left, 0 for still, 1 for right
        movementSpeed = random(5, 50);   // Add a movement speed of 5° to 50° every 20ms

        if (movement < 0) {                                       // If the head should move left
            headAngle = random(leftHeadAngle, servoHead.read());  // Set the final angle to the left
        } else if (movement > 0) {                                // If the head should move right
            headAngle = random(servoHead.read(), rightHeadAngle); // Set the final angle to the right
        }

        // Limit the angle between max left and max right
        headAngle = constrain(headAngle, leftHeadAngle, rightHeadAngle);

        if (movement != 0) {               // If the head is not still
            moveServo(servoHead, servoHead.read(), headAngle, movementSpeed);
        } else {
            delay(20);
            animationTime -= 20;
        }
    }
    servoHead.write(centerHeadAngle);     // Return the head to the initial position (90 degrees)
    delay(20);                            // Wait for the servo motor to finish moving  
}

void turnDownSwitch() {
    // Code to lower the switch with the arm only if the lid is lifted

    // If the lid is not open enough to clear the arm, open it enough.
    int lidPosition = servoLid.read();
    if (lidPosition < openingLidAngle) {
        servoLid.write(openingLidAngle);
        delay(20);                          // Wait for the servo motor to finish moving
    }
    
    // Vary the speed of arm movement by adding a delay
    moveServo(servoArm, servoArm.read(), angleMaximumAmplitude, random(5,50));
    digitalWrite(diodePin, LOW);            // Turn off the LED
    isSwoff = true;

    // Bring the arm back to angle 0 with a random speed
    moveServo(servoArm, servoArm.read(), angleMinimumAmplitude, random(5,50));

    // If the lid was moved to clear the arm, put it back as at the beginning of the function.
    if (lidPosition < openingLidAngle) {
        servoLid.write(lidPosition);
        delay(20);                          // Wait for the servo motor to finish moving
    }
}

void moveArm(){
    // Code to move the arm with the servo motor
    for (byte x = random(26); x > 0; x--) {
        moveServo(servoArm, servoArm.read(), random(angleMinimumAmplitude, angleMaximumAmplitude), random(5,50));
    }
}

void haveANervousBreakdown(){
    int numberOfClap = random(5,15);      // Number of clap that the lid will do.

    for( int x = 0; x < numberOfClap; x++)
    {
        moveServo(servoLid, closureLid, minOpeningLid, 5); // open the lid to the minimum angle
        moveServo(servoLid, minOpeningLid, closureLid, 5); // close the lid
    }
}

void randomBehavior(){

    unsigned long elapsedTime = millis() + random(2000, 30001);     // Time elapsed since program launch + animation time

    // As long as the animation time has not expired
    while (millis() <= elapsedTime ) {
        int randomAnimation = random(6);  // Random choice between 0 and 5

        switch(randomAnimation){
            case 0:
                moveLid();                  // move the lid
                break;
            case 1:
                headSpin();                  // move the head
                break;
            case 2:
                moveArm();                  // move the arm
                break;
            case 3:
                turnDownSwitch();           // turn down the switch
                break;
            case 4:
                haveANervousBreakdown();     // The plush have a nervous breadown
                break;
            case 5:
                // Delay without moving
                delay(random(500, 3001));  // Between 0.5 and 3 seconds
        }
    }

    // If the switch has not been turned down yet, do it
    if(!isSwoff) 
        turnDownSwitch();

    // Pick up the arm if it's still outside
    if(servoArm.read() > angleMinimumAmplitude)
        moveServo(servoArm, servoArm.read(), angleMinimumAmplitude, random(angleMinimumAmplitude, servoArm.read())); // Move the arm to angle 0

    //Close the lid if it is open
    if(servoLid.read() > closureLid)
        moveServo(servoLid, servoLid.read(), closureLid, random(closureLid, servoLid.read())); // Lift the lid to the specified angle
}
