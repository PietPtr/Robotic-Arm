#include <VarSpeedServo.h>

// Servos draw about 750-1000 mA
//#include <Servo.h>
#include <math.h>

#define TO_DEG 57.2957795

#define UPPER 11.0 // (a1) length of the first segment from the base
#define UNDER 11.0 // (a2) length of the second segment from the base

VarSpeedServo base;       // pin 2
VarSpeedServo shoulder;   // pin 3
VarSpeedServo elbow;      // pin 4
VarSpeedServo wrist;      // pin 5

const int BASE_PIN = 7;
const int SHOULDER_PIN = 6;
const int ELBOW_PIN = 5;
const int WRIST_PIN = 4;


const int POT0 = A0;
const int POT1 = A1;
const int POT2 = A5;

struct angles {
  float base;
  float shoulder;
  float elbow;
};

//
struct angles calc_angles(float arg_x, float arg_y, float arg_z) {
  struct angles a;

  // Can't reach this spot, return unchanged angles
  if (arg_z < 0) {
    return a;
  }

  float x = abs(arg_x);
  float y = abs(arg_y);
  float z = arg_z;


  a.base = (float)atan(x / y) * TO_DEG;

  double s1 = sqrt(pow(x, 2) + pow(y, 2));
  double s2 = sqrt(pow(s1, 2) + pow(z, 2));

  double alpha2 = acos(UPPER / (2 * s2) +
                       s2 / (2 * UPPER) -
                       pow(UNDER, 2) / (2 * UPPER * s2)) * TO_DEG;

  a.shoulder = 180 - (atan(z / s1) * TO_DEG) - alpha2;

  double sigma = acos(UNDER / (2 * UPPER) +
                      UPPER / (2 * UNDER) -
                      pow(s2, 2) / (2 * UPPER * UNDER)) * TO_DEG;

  a.elbow = 360 - 90 - sigma;

  if (arg_x < 0 && arg_y < 0) {
    a.shoulder = a.shoulder + (180 - 2 * a.shoulder);
  }

  if (arg_x < 0 && arg_y >= 0) {
    a.base = a.base + (180 - 2 * a.base);
  }
  if (arg_x >= 0 && arg_y < 0) {
    a.base = a.base + (180 - 2 * a.base);
    a.shoulder = a.shoulder + (180 - 2 * a.shoulder);
  }


  Serial.print("Base: ");
  Serial.println(a.base);
  //    Serial.print("Shoulder: ");
  //    Serial.println(a.shoulder);
  //    Serial.print("Elbow: ");
  //    Serial.println(a.elbow);

  return a;
}

void set_angles(struct angles ang) {
  base.write(ang.base, 30);
  shoulder.write(ang.shoulder, 30);
  elbow.write(ang.elbow, 30);
}

struct angles anglist[15];

void setup() {
  base.attach(BASE_PIN);
  shoulder.attach(SHOULDER_PIN);
  elbow.attach(ELBOW_PIN);
  wrist.attach(WRIST_PIN);

  Serial.begin(9600);

  //    for (int y = 15; y > 0; y--) {
  //        anglist[15 - y] = calc_angles(10, y, 10);
  //    }
}

void loop() {
  //    for(int i = 0; i < 15; i++) {
  //        set_angles(anglist[i]);
  //        delay(100);
  //    }
  //

//      point_quadrants();
  //    float y = -10 + (analogRead(POTPIN) / 1023.0) * 20;
  //
  //    Serial.println(y);
  //
  //    set_angles(calc_angles(-10, y, 1));
  //
  //    delay(50);

  //    sweep_y();

//      for (int i = 0; i < 180; i++) {
//          base.write(i, 0);
//  //        shoulder.write(i, 0);
//  //        elbow.write(i, 0);
//          delay(20);
//      }

    int val2 = analogRead(POT1);
    Serial.println(val2);

    delay(10);
    
    int val3 = analogRead(POT2);
    Serial.println(val3);
}

void point_quadrants() {
  set_angles(calc_angles(10, 10, 1));
  delay(1000);
  set_angles(calc_angles(-10, 10, 1));
  delay(1000);
  set_angles(calc_angles(-10, -10, 1));
  delay(1000);
  set_angles(calc_angles(10, -10, 1));
  delay(1000);
}

void sweep_y() {
  for (int i = 2; i < 15; i++) {
    set_angles(calc_angles(10, i, 10));
    delay(500);
  }

  for (int i = 15; i > 1; i--) {
    set_angles(calc_angles(10, i, 10));
    delay(500);
  }
}

void calibrate() {
  base.write(0, 0);
  shoulder.write(0, 0);
  elbow.write(0, 0);
}

