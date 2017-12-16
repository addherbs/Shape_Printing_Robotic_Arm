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
	
	
int main()
{
	InitEV3();

	std::string greeting("Hello World!");

	LcdPrintf(1, "%s\n", greeting.c_str());
	Wait(2000);

	FreeEV3();
	
}