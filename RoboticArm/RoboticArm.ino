// Servos draw about 750-1000 mA
#include <Servo.h>
#include <math.h>

Servo base;       // pin 2 
Servo shoulder;   // pin 3
Servo elbow;      // pin 4
Servo wrist;      // pin 5

const int BASE_PIN = 2;
const int SHOULDER_PIN = 3;
const int ELBOW_PIN = 4;
const int WRIST_PIN = 5;

struct angles {
    float base;
    float shoulder;
    float elbow;
};

// 
struct angles set_angles(float x, float y, float z) {
    struct angles a;

    // Can't reach this spot, return unchanged angles
    if (x < 0) {
        return a;
    }

    float base_angle = (float)atan(abs(x) / y);
    
    if (y < 0) {
        a.base = 90 - base_angle;
    } else if (y >= 0) {
        a.base = 90 + base_angle;
    }
    
}

void setup() {
    base.attach(BASE_PIN);
    shoulder.attach(SHOULDER_PIN);
    elbow.attach(ELBOW_PIN);
    wrist.attach(WRIST_PIN);

}

void loop() {

}
