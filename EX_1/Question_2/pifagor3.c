#include <stdio.h>

#include <math.h>

int main()
{

    // create a variable for each edge

    int x, y, z;

    printf("Please write the lengths of all 3 edges of the triangle (separated by space):");

    scanf("%d %d %d", &x, &y, &z);

    // a^2+b^2 = c^2

    if (pow(x, 2) + pow(y, 2) == pow(z, 2))
    {

        // create a variable for each angle in the triangle

        double xy, yz, zx;

        xy = M_PI / 2; // the 90 degree angle opposite to hypothenuse

        yz = asin((double)x / z);

        zx = asin((double)y / z);

        printf("Angle xy: %.2f radians\nAngle yz: %.2f radians\nAngle zx: %.2f radians\n", xy, yz, zx);
    }

    else if (pow(x, 2) + pow(z, 2) == pow(y, 2))
    {

        double xy, yz, zx;

        zx = M_PI / 2; // the 90 degree angle opposite to hypothenuse

        yz = asin((double)x / y);

        xy = asin((double)z / y);

        printf("Angle xy: %.2f radians\n Angle yz: %.2f radians\n Angle zx: %.2f radians\n", xy, yz, zx);
    }

    else if (pow(y, 2) + pow(z, 2) == pow(x, 2))
    {

        double xy, yz, zx;

        yz = M_PI / 2; // the 90 degree angle opposite to hypothenuse

        zx = asin((double)y / x);

        xy = asin((double)z / x);

        printf(" Angle xy: %.2f radians\nAngle yz: %.2f radians\nAngle zx: %.2f radians\n", xy, yz, zx);
    }

    else
    {

        printf("Error\n");
    }

    return 0;
}