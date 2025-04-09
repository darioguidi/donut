#include <stdio.h>
#include <math.h>

void getCoordinates(double R1, double R2, double theta, double *x, double *y, double *z){
    *x = R2 + R1 * cos(theta);
    *y = R1 * sin(theta);
    *z = 0.0;
}

int main(void){
    double R1 = 1.0;
    double R2 = 2.0;
    double theta = M_PI / 4;  // 45 gradi
    

    double x, y, z;
    getCoordinates(R1, R2, theta, &x, &y, &z);

    printf("x = %f, y = %f, z = %f\n", x, y, z);

    return 0;
}