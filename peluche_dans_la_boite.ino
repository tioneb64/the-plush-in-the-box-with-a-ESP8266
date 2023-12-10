#include <Servo.h>
const int switchPin    = 11;  // Broche pour l'interrupteur
const int servoLidPin  = 12;  // Broche pour le servo moteur du couvercle
const int servoArmPin  = 13;  // Broche pour le servo moteur du bras
const int servoHeadPin = 14;  // Broche pour le servo moteur de la tête
const int diodePin     = 15;  // Broche pour la LED

Servo servoLid;
Servo servoHarm;
Servo servoHead;

int openingLidAngle        = 0;    // Position minimale d'ouverture du couvercle pour étendre le bras
int angleMaximumAmplitude  = 90;   // Amplitude maximale du servo moteur du bras (servoHarm)
int maxOpeningMid          = 51;   // Angle d'ouverture maximal du couvercle.
int minOpeningLid          = 15;   // Angle d'ouverture minimal du couvercle.
int closureLid             =  0;   // Angle auquel le couvercle est considéré comme fermé
int leftHeadAngle          = 40;   // Angle maximal à gauche pour tourner la tête
int centerHeadAngle        = 90;   // Angle centré en regardant droit
int rightHeadAngle         = 140;  // Angle maximal à droite pour tourner la tête

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(diodePin, OUTPUT);
  servoLid.attach(servoLidPin);
  servoHarm.attach(servoArmPin);
  servoHead.attach(servoHeadPin);

  // Initialiser d'autres configurations si nécessaire
}

void loop() {

    // Vérifier l'état de l'interrupteur
    if (digitalRead(switchPin) == HIGH) {
        digitalWrite(diodePin, HIGH);       // Allumer la LED
        randomBehavior();
    }
}

int moveServo(Servo& servo, int currentPosition, int finalPosition, int speed) {
    
    int newPosition = 0;
    int elapsedAnimation = 0;

    if (finalPosition < currentPosition)
        speed = speed * -1; // Rendre la vitesse négative si la position actuelle est supérieure à la position finale

    while (servo.read() != finalPosition) {

        newPosition = servo.read() + speed;

        // Limiter les débordements
        newPosition = constrain(currentPosition + speed, finalPosition, currentPosition);
        servo.write(newPosition);
        delay(10); // Attendre que le servo moteur ait fini de bouger
        elapsedAnimation += 10;
    }

    return elapsedAnimation;
}

void moveLid() {
    // Code pour lever le couvercle avec le servo moteur
    if (servoLid.read() > closureLid) // Couvercle déjà ouvert, donc le fermer
        moveServo(servoLid, servoLid.read(), closureLid, random(5, 50)); // Lever le couvercle à l'angle spécifié
    else
        moveServo(servoLid, servoLid.read(), random(minOpeningLid, maxOpeningMid), random(5, 50)); // Lever le couvercle à l'angle spécifié
}

void turnDownSwitch() {
    // Code pour baisser l'interrupteur avec le bras uniquement si le couvercle est levé

    // Si le couvercle n'est pas assez ouvert pour dégager le bras, l'ouvrir davantage.
    int lidPosition = servoLid.read();
    if (lidPosition < openingLidAngle) {
        servoLid.write(openingLidAngle);
        delay(20);                          // Attendre que le servo moteur ait fini de bouger
    }
    
    // Variabilité de la vitesse du mouvement du bras en ajoutant un délai
    int movementSpeed = random(0, angleMaximumAmplitude);
    moveServo(servoHarm, servoHarm.read(), angleMaximumAmplitude, movementSpeed);
    digitalWrite(diodePin, LOW); // Éteindre la LED

    // Ramener le bras à l'angle 0 avec une vitesse aléatoire
    movementSpeed = random(0, servoHarm.read());
    moveServo(servoHarm, servoHarm.read(), minOpeningLid, movementSpeed);

    // Si le couvercle a été déplacé pour dégager le bras, le remettre comme au début de la fonction.
    if (lidPosition < openingLidAngle) {
        servoLid.write(lidPosition);
        delay(20);                          // Attendre que le servo moteur ait fini de bouger
    }
}

void headSpin() {
    // Code pour tourner aléatoirement la tête

    int animationTime = random(0, 3001); // Animation aléatoire entre 0 et 3000 ms
    int headAngle   = 0;                 // Position finale de la tête
    int movement   = 0;                  // Détermine si la tête doit bouger à gauche, à droite, ou rester immobile
    int movementSpeed   = 0;             // Vitesse de mouvement de la tête
  //  int currentPosition = 0;           // Position courante de la tête

    while (animationTime > 0) {

        // Déterminer si la tête doit bouger à gauche, à droite, ou rester immobile
        movement = random(-1, 2);        // -1 pour la gauche, 0 pour immobile, 1 pour la droite
        movementSpeed = random(5, 50);   // Ajouter une vitesse de mouvement de 5° à 50° toutes les 20 ms

        if (movement < 0) {                                       // Si la tête doit bouger à gauche
            headAngle = random(leftHeadAngle, servoHead.read());  // Définir l'angle final à gauche
        } else if (movement > 0) {                                // Si la tête doit bouger à droite
            headAngle = random(servoHead.read(), rightHeadAngle); // Définir l'angle final à droite
        }

        // Limiter l'angle entre l'extrême gauche et l'extrême droite
        headAngle = constrain(headAngle, leftHeadAngle, rightHeadAngle);

        if (movement != 0) {               // Si la tête n'est pas immobile
            animationTime -= moveServo(servoHead, servoHead.read(), headAngle, movementSpeed);
        } else {
            delay(20);
            animationTime -= 20;
        }
    }

    servoHead.write(centerHeadAngle);     // Ramener la tête à la position initiale (90 degrés)
    delay(20);                            // Attendre que le servo moteur ait fini de bouger  
}

void randomBehavior(){

    int numberOfOpenings = random(1, 6);  // Entre 1 et 5 ouvertures
    int armActivation = 0;                // 0=bras pas encore activé, 1=bras déjà activé

    // Si le couvercle doit être levé plus d'une fois, décider à quelle ouverture activer le bras
    if (numberOfOpenings > 1)
        armActivation = random(1, numberOfOpenings);
    else
        armActivation = 1;            // Sinon, activer le bras la première fois
  
    for (int i = 0; i < numberOfOpenings; ++i) {

        moveLid();                        // Lever le couvercle

        // Tourner la tête et déterminer la durée d'ouverture
        headSpin();

        // Si c'est l'ouverture où le bras doit être activé
        if (i == armActivation) {
            turnDownSwitch();
        }

        // Tourner la tête et déterminer la durée d'ouverture
        headSpin();

        // Fermer le couvercle
        moveLid();

        // Délai avant la prochaine ouverture
        delay(random(1000, 5000));
    }
}
