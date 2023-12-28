#include <Servo.h>

// Définition des constantes de broches
const int switchPin    = 12;  // Broche pour l'interrupteur
const int servoLidPin  = 13;  // Broche pour le servo-moteur du couvercle
const int servoArmPin  = 14;  // Broche pour le servo-moteur du bras
const int servoHeadPin = 15;  // Broche pour le servo-moteur de la tête
const int diodePin     = 16;  // Broche pour la LED

Servo servoLid;             // Servo-moteur pour le couvercle
Servo servoArm;             // Servo-moteur pour le bras
Servo servoHead;            // Servo-moteur pour la tête

// Définition des constantes d'angle
const int angleMinimumAmplitude  =   0;   // Amplitude minimale du servo-moteur du bras
const int angleMaximumAmplitude  = 120;   // Amplitude maximale du servo-moteur du bras
const int openingLidAngle        =   0;   // Position minimale d'ouverture du couvercle pour étendre le bras
const int maxOpeningMid          =  51;   // Angle d'ouverture maximale du couvercle.
const int minOpeningLid          =  15;   // Angle d'ouverture minimale du couvercle.
const int closureLid             =   0;   // Angle auquel le couvercle est considéré comme fermé
const int leftHeadAngle          =  40;   // Angle maximal à gauche pour tourner la tête
const int centerHeadAngle        =  90;   // Angle central pour regarder droit devant
const int rightHeadAngle         = 140;   // Angle maximal à droite pour tourner la tête

bool isSwoff                     = false; // Indique si le bras a abaissé l'interrupteur ou non

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(diodePin, OUTPUT);
  servoLid.attach(servoLidPin);
  servoArm.attach(servoArmPin);
  servoHead.attach(servoHeadPin);
}

void loop() {
    // Vérifie l'état de l'interrupteur
    if (digitalRead(switchPin) == HIGH) {
        digitalWrite(diodePin, HIGH);       // Allume la LED
        isSwoff = false;
        randomBehavior();
    }
}

void moveServo(Servo& servo, int currentPosition, int finalPosition, int speed) {
    
    int newPosition = 0;
    int elapsedAnimation = 0;

    if (finalPosition < currentPosition)
        speed = speed * -1; // Rend la vitesse négative si la position actuelle est supérieure à la position finale

    while (servo.read() != finalPosition) {

        newPosition = servo.read() + speed;

        // Limite les débordements
        newPosition = constrain(currentPosition + speed, finalPosition, currentPosition);
        servo.write(newPosition);
        delay(10); // Attend que le servo-moteur ait fini de bouger
        elapsedAnimation += 10;
    }
}

void moveLid() {
    // Soulève le couvercle avec le servo-moteur
    if (servoLid.read() > closureLid) // Le couvercle est déjà ouvert, donc on le ferme
        moveServo(servoLid, servoLid.read(), closureLid, random(5, 50)); // Soulève le couvercle à l'angle spécifié
    else
        moveServo(servoLid, servoLid.read(), random(minOpeningLid, maxOpeningMid), random(5, 50)); // Soulève le couvercle à l'angle spécifié
}

void headSpin() {
    // Tourne la tête de manière aléatoire
    int animationTime = random(0, 5001); // Temps d'animation aléatoire entre 0 et 5000 ms
    int headAngle   = 0;                 // Position finale de la tête
    int movement   = 0;                  // Détermine si la tête doit se déplacer à gauche, à droite, ou rester immobile
    int movementSpeed   = 0;             // Vitesse de mouvement de la tête
  //  int currentPosition = 0;           // Position actuelle de la tête

    while (animationTime > 0) {

        // Détermine si la tête doit se déplacer à gauche, à droite, ou rester immobile
        movement = random(-1, 2);        // -1 pour la gauche, 0 pour immobile, 1 pour la droite
        movementSpeed = random(5, 50);   // Ajoute une vitesse de mouvement de 5° à 50° toutes les 20 ms

        if (movement < 0) {                                       // Si la tête doit se déplacer à gauche
            headAngle = random(leftHeadAngle, servoHead.read());  // Définit l'angle final à gauche
        } else if (movement > 0) {                                // Si la tête doit se déplacer à droite
            headAngle = random(servoHead.read(), rightHeadAngle); // Définit l'angle final à droite
        }

        // Limite l'angle entre l'extrême gauche et l'extrême droite
        headAngle = constrain(headAngle, leftHeadAngle, rightHeadAngle);

        if (movement != 0) {               // Si la tête ne reste pas immobile
            moveServo(servoHead, servoHead.read(), headAngle, movementSpeed);
        } else {
            delay(20);
            animationTime -= 20;
        }
    }
    servoHead.write(centerHeadAngle);     // Ramène la tête à la position initiale (90 degrés)
    delay(20);                            // Attend que le servo-moteur ait fini de bouger  
}

void turnDownSwitch() {
    // Abaisse l'interrupteur avec le bras uniquement si le couvercle est soulevé

    // Si le couvercle n'est pas assez ouvert pour dégager le bras, ouvrez-le assez.
    int lidPosition = servoLid.read();
    if (lidPosition < openingLidAngle) {
        servoLid.write(openingLidAngle);
        delay(20);                          // Attend que le servo-moteur ait fini de bouger
    }
    
    // Varie la vitesse de mouvement du bras en ajoutant un délai
    moveServo(servoArm, servoArm.read(), angleMaximumAmplitude, random(5,50));
    digitalWrite(diodePin, LOW);            // Éteint la LED
    isSwoff = true;

    // Ramène le bras à l'angle 0 avec une vitesse aléatoire
    moveServo(servoArm, servoArm.read(), angleMinimumAmplitude, random(5,50));

    // Si le couvercle a été déplacé pour dégager le bras, remettez-le comme au début de la fonction.
    if (lidPosition < openingLidAngle) {
        servoLid.write(lidPosition);
        delay(20);                          // Attend que le servo-moteur ait fini de bouger
    }
}

void moveArm(){
    // Déplace le bras avec le servo-moteur
    for (byte x = random(26); x > 0; x--) {
        moveServo(servoArm, servoArm.read(), random(angleMinimumAmplitude, angleMaximumAmplitude), random(5,50));
    }
}

void haveANervousBreakdown(){
    int numberOfClap = random(5,15);      // Nombre de claques que le couvercle effectuera.

    for( int x = 0; x < numberOfClap; x++)
    {
        moveServo(servoLid, closureLid, minOpeningLid, 5); // ouvrir le couvercle à l'angle minimum
        moveServo(servoLid, minOpeningLid, closureLid, 5); // fermer le couvercle
    }
}

void randomBehavior(){

    unsigned long elapsedTime = millis() + random(2000, 30001);     // Temps écoulé depuis le lancement du programme + temps d'animation

    // Tant que le temps d'animation n'est pas écoulé
    while (millis() <= elapsedTime ) {
        int randomAnimation = random(6);  // Choix aléatoire entre 0 et 5

        switch(randomAnimation){
            case 0:
                moveLid();                  // déplace le couvercle
                break;
            case 1:
                headSpin();                  // déplace la tête
                break;
            case 2:
                moveArm();                  // déplace le bras
                break;
            case 3:
                turnDownSwitch();           // abaisse l'interrupteur
                break;
            case 4:
                haveANervousBreakdown();     // Le jouet en peluche a une crise de nerfs
                break;
            case 5:
                // Délai sans mouvement
                delay(random(500, 3001));  // Entre 0.5 et 3 secondes
        }
    }

    // Si l'interrupteur n'a pas encore été abaissé, le faire
    if(!isSwoff) 
        turnDownSwitch();

    // Relevez le bras s'il est toujours à l'extérieur
    if(servoArm.read() > angleMinimumAmplitude)
        moveServo(servoArm, servoArm.read(), angleMinimumAmplitude, random(angleMinimumAmplitude, servoArm.read())); // Déplace le bras à l'angle 0

    // Fermez le couvercle s'il est ouvert
    if(servoLid.read() > closureLid)
        moveServo(servoLid, servoLid.read(), closureLid, random(closureLid, servoLid.read())); // Soulève le couvercle à l'angle spécifié
}
