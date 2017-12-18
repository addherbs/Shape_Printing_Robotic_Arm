#include <ev3.h>
#include <string>
#include <math.h>

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

// Tan(theta) = OPP_SIDE / ADJ_SIDE
void decideDirection(int x0, int y0, int x1, int y1) {
    int x_diff = 0, y_diff = 0;
    double theta = 0.0, hypotenuse = 0.0;

    if (x0 < x1) {
        x_diff = x1 - x0;
        LcdPrintf(1, "XD %d ", x_diff);
        if (y0 < y1) {
            //Go Diagonal Right to Left Top (8)
            
        } else if (y0 > y1) {
            //Go Diagonal Left to Right Top (7)
            
        } else if (y0 == y1) {
            // Vertical Bottom to Top (4)

        }
    } else if (x0 > x1) {
        x_diff = x0 - x1;
        LcdPrintf(1, "XD %d ", x_diff);
        if (y0 < y1) {
            //Go Diagonal Right to Left Bottom (6)
        } else if (y0 > y1) {
            //Go Diagonal Left to Right Bottom (5)
        } else if (y0 == y1) {
            // Vertical Top to Bottom (3)
        }
    } else {
        // Here, x0 and X1 will be equal
        // Because all other test cases will be done before this
        if (y0 < y1) {
            // Horizontal Right to Left (2)
            
        } else if (y0 > y1) {
            // Horizontal Left to Right (1)
        }
    }
}

	
int main()
{
	InitEV3();

	std::string greeting("Hello World!");

	LcdPrintf(1, "%s\n", greeting.c_str());
	Wait(2000);

	FreeEV3();
	
}