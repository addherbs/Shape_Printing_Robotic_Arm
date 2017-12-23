#include <ev3.h>
#include <string>
#include <math.h>
#define PI 3.14159265
double calculate_tan_inverse(int x, int y) {
    double division, tan_inservse;
    division = (double) x / y;
    tan_inservse = atan(division) * 180 / PI;
    return tan_inservse;
}
void HorizontalLeftRight(int speed, int time) {
    OnFwdReg(OUT_C, speed);
    OnFwdReg(OUT_B, speed);
    Wait(time);
}
void HorizontRightLeft(int speed, int time) {
    OnRevReg(OUT_C, speed);
    OnRevReg(OUT_B, speed);
    Wait(time);
}
void VerticalTopBottom(int speed, int time) {
    OnRevReg(OUT_C, speed);
    OnFwdReg(OUT_B, speed);
    Wait(time);
}
void VerticalBottomTop(int speed, int time) {
    OnFwdReg(OUT_C, speed);
    OnRevReg(OUT_B, speed);
    Wait(time);
}
void DiagonalLeftRightBottom(int speedB, int speedC, int time) {
    OnRevReg(OUT_C, speedC);
    OnFwdReg(OUT_B, speedB);
    Wait(time);
}
void DiagonalRightLeftBottom(int speedB, int speedC, int time) {
    OnRevReg(OUT_C, speedC);
    OnFwdReg(OUT_B, speedB);
    Wait(time);
}
void DiagonalLeftRightTop(int speedB, int speedC, int time) {
    OnFwdReg(OUT_C, speedC);
    OnRevReg(OUT_B, speedB);
    Wait(time);
}
void DiagonalRightLeftTop(int speedB, int speedC, int time) {
    OnFwdReg(OUT_C, speedC);
    OnRevReg(OUT_B, speedB);
    Wait(time-150);
}

int getFinalDegreeFromRange(int degree) {

    if (degree <= 30) {
        return 45;
    }
    if (degree <= 60) {
        return 45;
    }
    if (degree > 60) {
        return 75;
    }
    return 0;
}

int getSpeedB(int degree) {
    switch (degree) {
    case 30:
        return 35;
    case 45:
        return 35;
    case 75:
        return 45;
    }
    return 0;
}

int getSpeedC(int degree) {
    switch (degree) {
    case 30:
        return 10;
    case 45:
        return 10;
    case 75:
        return 20;
    }
    return 0;
}

int getTimeForDegree(int degree) {
    switch (degree) {
    case 30:
        return 1250;
    case 45:
        return 1250;
    case 75:
        return 1250;
    }
    return 0;
}

void moveDiagonal(int diagonalCase, double degree, double hypotenuse) {
    int final_degree = 0;
    final_degree = getFinalDegreeFromRange((int) degree);
    int speedB = getSpeedB(final_degree);
    int speedC = getSpeedC(final_degree);
    int time = getTimeForDegree(final_degree);
    LcdPrintf(1, "MD %d %f\n", final_degree, hypotenuse);
    switch (diagonalCase) {
    case 5: //Diagonally left to right in bottom direction
        LcdPrintf(1, "C5 ");
        for (int i = 0; i < hypotenuse; i++) {
            DiagonalLeftRightBottom(speedB, speedC, time);
        }
        break;
    case 6: //Diagonally right to left in bottom direction
        LcdPrintf(1, "C6 ");
        for (int i = 0; i < hypotenuse; i++) {
            DiagonalRightLeftBottom(speedC, speedB, time);
        }
        break;
    case 7: //Diagonally left to right in top direction
        LcdPrintf(1, "C7 ");
        for (int i = 0; i < hypotenuse; i++) {
            DiagonalLeftRightTop(speedC, speedB, time);
        }
        break;
    case 8: //Diagonally right to left in top direction
        LcdPrintf(1, "C8 ");
        for (int i = 0; i < hypotenuse; i++) {
            DiagonalRightLeftTop(speedB, speedC, time);
        }
        break;
    default:
        break;
    }
}

// Tan(theta) = OPP_SIDE / ADJ_SIDE
void decideDirection(int x0, int y0, int x1, int y1) {
    int x_diff = 0, y_diff = 0;
    double theta = 0.0, hypotenuse = 0.0;

    if (x0 < x1) {
        x_diff = x1 - x0;
        LcdPrintf(1, "XD %d ", x_diff);
        if (y0 < y1) {
            //Go Diagonal Right to Left Top (8)
            y_diff = y1 - y0;
            theta = calculate_tan_inverse((double) y_diff, (double) x_diff);
//            hypotenuse = ceil(hypot(y_diff, x_diff));
            hypotenuse = ceil(sqrt(y_diff * y_diff + x_diff * x_diff));

            moveDiagonal(8, theta, hypotenuse);
        } else if (y0 > y1) {
            //Go Diagonal Left to Right Top (7)
            y_diff = y0 - y1;
            theta = calculate_tan_inverse(y_diff, x_diff);
            hypotenuse = ceil(sqrt(y_diff * y_diff + x_diff * x_diff));
            moveDiagonal(7, theta, hypotenuse);
        } else if (y0 == y1) {
            // Vertical Bottom to Top (4)
            //------------- Move Arm Vertically in Front for X_Difference Blocks----------------------

            LcdPrintf(1, "VBT %d ", x_diff);
            for (int i = 0; i < x_diff; i++) {

                VerticalBottomTop(10, 1666);
            }
            //----------------------------------------------------------------------
        }
    } else if (x0 > x1) {
        x_diff = x0 - x1;
        LcdPrintf(1, "XD %d ", x_diff);
        if (y0 < y1) {
            //Go Diagonal Right to Left Bottom (6)
            y_diff = y1 - y0;
            theta = calculate_tan_inverse(y_diff, x_diff);
            hypotenuse = ceil(sqrt(y_diff * y_diff + x_diff * x_diff));
            moveDiagonal(6, theta, hypotenuse);
        } else if (y0 > y1) {
            //Go Diagonal Left to Right Bottom (5)
            y_diff = y0 - y1;
            theta = calculate_tan_inverse(y_diff, x_diff);
            hypotenuse = ceil(sqrt(y_diff * y_diff + x_diff * x_diff));
            moveDiagonal(5, theta, hypotenuse);
        } else if (y0 == y1) {
            // Vertical Top to Bottom (3)
            LcdPrintf(1, "VTB %d ", x_diff);
            //------------- Move Arm Vertically Back for X_Difference Blocks----------------------
            for (int i = 0; i < x_diff; i++) {
                VerticalTopBottom(10, 666);
            }
            //----------------------------------------------------------------------
        }
    } else {
        // Here, x0 and X1 will be equal
        // Because all other test cases will be done before this
        if (y0 < y1) {
            // Horizontal Right to Left (2)
            y_diff = y1 - y0;
            LcdPrintf(1, "YD %d ", y_diff);
            //------------- Move Arm Horizontally Left in Y_DIFFEREBCE Blocks----------------------
            for (int i = 0; i < y_diff; i++) {
                std::string HRL("HRL!");
                LcdPrintf(1, "%s  ", HRL.c_str());
                HorizontRightLeft(10, 2500);
            }
            //----------------------------------------------------------------
        } else if (y0 > y1) {
            // Horizontal Left to Right (1)
            y_diff = y0 - y1;
            LcdPrintf(1, "YD %d ", y_diff);
            //------------- Move Arm Horizontally Right in Y_DIFFEREBCE Blocks----------------------
            for (int i = 0; i < y_diff; i++) {
                std::string HLR("HLR!");
                LcdPrintf(1, "%s  ", HLR.c_str());
                HorizontalLeftRight(10, 2500);
            }
            //----------------------------------------------------------------
        }
    }
}

//void gotoInitialPosition(int x1, int y1) {
//    int x0 = 1, y0 = 5;
//    decideDirection(x0, y0, x1, y1);
//    OnFwdReg(OUT_A, -50);
//    Off(OUT_A);
//}

int main() {
    InitEV3();

//OnFwdReg(OUT_A, 50);

    int coordinates[11][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
            { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
//  Set Coordinate Values
    coordinates[0][0] = 3;
    coordinates[0][1] = 5;
    coordinates[1][0] = 5;
    coordinates[1][1] = 3;
    coordinates[2][0] = 4;
    coordinates[2][1] = 1;
    coordinates[3][0] = 1;
    coordinates[3][1] = 1;
    coordinates[4][0] = 1;
    coordinates[4][1] = 3;
    coordinates[5][0] = 3;
    coordinates[5][1] = 5;

    int iterations = 0;
//Calculate Number Of (Co-ordinates)iterations
    for (int i = 0; i < 10; i++) {
        if (coordinates[i][0] == 0 && coordinates[i][1] == 0) {
            break;
        }
        iterations++;
    }

//Set Final Coordinate to the first coordinate
    coordinates[iterations][0] = coordinates[0][0];
    coordinates[iterations][1] = coordinates[0][1];

////Go To The Initial Position
//    gotoInitialPosition(coordinates[0][0], coordinates[0][1]);

// Main Loop
// From Initial Position to Track Path and Go Back To Initial Position
    int count = 0;
    while (count < iterations - 1) {
        // Sending Current Position(x0,y0) and next position(x1,y1) values
        std::string forL("FOR");
        LcdPrintf(1, "%s ", forL.c_str());
        decideDirection(coordinates[count][0], coordinates[count][1],
                coordinates[count + 1][0], coordinates[count + 1][1]);
        count++;
    }
    FreeEV3();
}