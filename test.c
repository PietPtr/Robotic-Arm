#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define TO_DEG 57.2957795

#define UPPER 5.0 // (a1) length of the first segment from the base
#define UNDER 4.0 // (a2) length of the second segment from the base

struct angles {
    float base;
    float shoulder;
    float elbow;
};

// Converts three dimensional coordinates to angles
struct angles set_angles(float x, float y, float z) {
    struct angles a;

    // Can't reach this spot, return unchanged angles
    if (x < 0) {
        printf("Error: arm does not support position");
        return a;
    }

    a.base = 90 - (float)atan(x / y) * TO_DEG;

    double s1 = sqrt(pow(x, 2) + pow(y, 2));
    double s2 = sqrt(pow(s1, 2) + pow(z, 2));
    // printf("s1: %f, s2: %f\n", s1, s2);

    double alpha2 = acos(UPPER / (2 * s2) +
                         s2 / (2 * UPPER) -
                         pow(UNDER, 2) / (2 * UPPER * s2)) * TO_DEG;
    // printf("alpha2: %f\n", alpha2);

    a.shoulder = 180 - (atan(z / s1) * TO_DEG) - alpha2;

    double sigma = acos(UNDER / (2 * UPPER) +
                        UPPER / (2 * UNDER) -
                        pow(s2, 2) / (2 * UPPER * UNDER)) * TO_DEG;

   // printf("sigma: %f\n", sigma);

    a.elbow = 360 - 90 - sigma;

    // printf("\nBase:      %f\nShoulder:  %f\nElbow:     %f \n\n\n",
    //     a.base, a.shoulder, a.elbow);

    // printf("(%f, %f),", a.shoulder, a.elbow);

    return a;
}

int main(int argc, char* argv[]) {
    // set_angles(5, 3, 6);

    // for (int i = 1; i < 35; i++) {
    //     set_angles(4, 0, i / 5.0);
    // }
    // for (int i = 34; i >= 0; i--) {
    //     set_angles(5, 0, i / 5.0);
    // }
    // printf("\n");

    float x = atof(argv[1]);
    float y = atof(argv[2]);
    float z = atof(argv[3]);

    struct angles a = set_angles(x, y, z);

    printf("%f %f %f", a.base, a.shoulder, a.elbow);

    return 0;
}
