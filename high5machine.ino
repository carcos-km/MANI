/* MANI : The High 5 Machine
  by Clara Arcos
  uses VarSpeedServo library
  by NETLab Toolkit Group <https://github.com/netlabtoolkit/VarSpeedServo>
*/

#include <VarSpeedServo.h>

// create servo objects
VarSpeedServo servoFB;  // forwards and backwards
VarSpeedServo servoSS;  // side to side

#define START_ANGLE_FB 80
#define START_ANGLE_SS 76

// define position squares
typedef enum {
  FL,  // front left
  FC,  // front center
  FR,  // front right
  BL,  // back left
  BC,  // back center
  BR   // back right
} Square;

Square getSquare() {  // returns current position square
  int FB_pos = servoFB.read();
  int SS_pos = servoSS.read();

  if (FB_pos < 80) {           // we're front
    if (SS_pos < 66) {         // we're left
      return FL;
    } else if (SS_pos > 86) {  // we're right
      return FR;
    } else {
      return FC;               // we're center
    }
  } else {                     // we're back
    if (SS_pos < 66) {         // we're left
      return BL;
    } else if (SS_pos > 86) {  // we're right
      return BR;
    } else {
      return BC;               // we're center
    }
  }
}

void gotoSquare(Square square) {    // moves to specified square
  switch (square) {
    case FL:
      servoFB.write(80, 50, true);  // move to 80 degrees, speed of 50, wait until complete
      servoSS.write(65, 50, true);
      break;
    case FC:
      servoFB.write(80, 50, true);
      servoSS.write(76, 50, true);
      break;
    case FR:
      servoFB.write(80, 50, true);
      servoSS.write(87, 50, true);
      break;
    case BL:
      servoFB.write(60, 50, true);
      servoSS.write(65, 50, true);
      break;
    case BC:
      servoFB.write(60, 50, true);
      servoSS.write(76, 50, true);
      break;
    case BR:
      servoFB.write(60, 50, true);
      servoSS.write(87, 50, true);
      break;
    default:
      Serial.println(square);
  }
  
}

void setup() {
  Serial.begin(9600);
  servoFB.attach(5);
  servoSS.attach(6);
  pinMode(7, INPUT);
  servoFB.write(START_ANGLE_FB, 50, true);
  servoSS.write(START_ANGLE_SS, 50, true);
}

void loop() {
  int status = digitalRead(7);
  if (status == LOW) {                    // if an obstacle is detected
    Square current_square = getSquare();  // get current square
    switch (current_square) {
      case FL:                            // if we're in front left
        switch (random(5)) {              // generate a random number up to 5
          case 0: gotoSquare(FC); break;  // if the random number is 0 go to front centre
          case 1: gotoSquare(FR); break;
          case 2: gotoSquare(BL); break;
          case 3: gotoSquare(BC); break;
          case 4: gotoSquare(BR); break;
        }
        break;
      case FC:
        switch (random(5)) {
          case 0: gotoSquare(FL); break;
          case 1: gotoSquare(FR); break;
          case 2: gotoSquare(BL); break;
          case 3: gotoSquare(BC); break;
          case 4: gotoSquare(BR); break;
        }
        break;
      case FR:
        switch (random(5)) {
          case 0: gotoSquare(FL); break;
          case 1: gotoSquare(FC); break;
          case 2: gotoSquare(BL); break;
          case 3: gotoSquare(BC); break;
          case 4: gotoSquare(BR); break;
        }
        break;
      case BL:
        switch (random(4)) {
          case 0: gotoSquare(FC); break;
          case 1: gotoSquare(FR); break;
          case 2: gotoSquare(BC); break;
          case 3: gotoSquare(BR); break;
        }
        break;
      case BC:
        switch (random(4)) {
          case 0: gotoSquare(FL); break;
          case 1: gotoSquare(FR); break;
          case 2: gotoSquare(BL); break;
          case 3: gotoSquare(BR); break;
        }
        break;
      case BR:
        switch (random(4)) {
          case 0: gotoSquare(FL); break;
          case 1: gotoSquare(FC); break;
          case 2: gotoSquare(BL); break;
          case 3: gotoSquare(BC); break;
        }
        break;
      default:
        Serial.println(current_square);
    }
  } else {
    Serial.println("All clear"); // print in serial if there is no obstacle
  }
}
