#include <Servo.h>
const int switchPin    = 11;  // Pin for the switch
const int servoLidPin  = 12;  // Pin for the lid servo motor
const int servoArmPin  = 13;  // Pin for the arm servo motor
const int servoHeadPin = 14;  // Pin for the head servo motor
const int diodePin     = 15;  // Pin for the LED

Servo servoLid;
Servo servoHarm;
Servo servoHead;

int openingLidAngle        = 0;    // Minimum lid opening position to extend the arm
int angleMaximumAmplitude  = 90;   // Maximum amplitude of the arm servo motor (servoHarm)
int maxOpeningMid          = 51;   // Maximum opening angle of the lid.
int minOpeningLid          = 15;   // Minimum opening angle of the lid.
int closureLid             =  0;   // Angle at which the lid is considered closed
int leftHeadAngle          = 40;   // Maximum left angle to turn the head
int centerHeadAngle        = 90;   // Centered head looking straight
int rightHeadAngle         = 140;  // Maximum right angle to turn the head

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(diodePin, OUTPUT);
  servoLid.attach(servoLidPin);
  servoHarm.attach(servoArmPin);
  servoHead.attach(servoHeadPin);

  // Initialize other configurations if needed
}

void loop() {

    // Check the state of the switch
    if (digitalRead(switchPin) == HIGH) {
        digitalWrite(diodePin, HIGH);       // Turn on the LED
        randomBehavior();
    }
}

int moveServo(Servo& servo, int currentPosition, int finalPosition, int speed) {
    
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

    return elapsedAnimation;
}

void moveLid() {
    // Code to lift the lid with the servo motor
    if (servoLid.read() > closureLid) // Lid already open, so close it
        moveServo(servoLid, servoLid.read(), closureLid, random(5, 50)); // Lift the lid to the specified angle
    else
        moveServo(servoLid, servoLid.read(), random(minOpeningLid, maxOpeningMid), random(5, 50)); // Lift the lid to the specified angle
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
    int movementSpeed = random(0, angleMaximumAmplitude);
    moveServo(servoHarm, servoHarm.read(), angleMaximumAmplitude, movementSpeed);
    digitalWrite(diodePin, LOW); // Turn off the LED

    // Bring the arm back to angle 0 with a random speed
    movementSpeed = random(0, servoHarm.read());
    moveServo(servoHarm, servoHarm.read(), minOpeningLid, movementSpeed);

    // If the lid was moved to clear the arm, put it back as at the beginning of the function.
    if (lidPosition < openingLidAngle) {
        servoLid.write(lidPosition);
        delay(20);                          // Wait for the servo motor to finish moving
    }
}

void headSpin() {
    // Code to randomly turn the head

    int animationTime = random(0, 3001); // Random animation time between 0 and 3000 ms
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
            animationTime -= moveServo(servoHead, servoHead.read(), headAngle, movementSpeed);
        } else {
            delay(20);
            animationTime -= 20;
        }
    }

    servoHead.write(centerHeadAngle);     // Return the head to the initial position (90 degrees)
    delay(20);                            // Wait for the servo motor to finish moving  
}

void randomBehavior(){

    int numberOfOpenings = random(1, 6);  // Between 1 and 5 openings
    int armActivation = 0;                // 0=arm not yet activated, 1=arm already activated

    for (int i = 0; i < numberOfOpenings; ++i) {

        // If the lid needs to be lifted more than once, decide at which opening to activate the arm
        if (numberOfOpenings > 1)
            armActivation = random(1, numberOfOpenings);
        else
            armActivation = 1;            // If not, activate the arm the first time

        moveLid();                        // Lift the lid

        // Spin the head and determine the opening time
        headSpin();

        // If it's the opening where the arm should be activated
        if (i == armActivation) {
            turnDownSwitch();
        }

        // Spin the head and determine the opening time
        headSpin();

        // Close the lid
        moveLid();

        // Delay before the next opening
        delay(random(1000, 5000));
    }
}
