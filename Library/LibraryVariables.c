#include <stdbool.h>
#include "OKHeader.h"
#include "GameVariables/NTSC/GameOffsets.h"
int GlobalAddressA, GlobalAddressB, GlobalAddressC;
int GlobalIntA, GlobalIntB, GlobalIntC, GlobalIntD;
float GlobalFloatA;
char GlobalCharA,GlobalCharB,GlobalCharC,GlobalCharD;
short GlobalShortA, GlobalShortB;
bool GlobalBoolA, GlobalBoolB, GlobalBoolC, GlobalBoolD;

int LoopValue;

//MarioKart3D Variables
int CoinCount = 0;
float AffineMatrix[4][4];
float objectPosition[3] = {0,0,0};
float objectVelocity[3] = {0,0,0};
short objectAngle[3] = {0,0,0};
short objectIndex;
//
//



//Mario Kart Stats
char StatsID;


//SharedFunctions
long dataLength = 0; //
long *targetAddress = &ok_Target;
long *sourceAddress = &ok_Source;
long *tempPointer = &ok_Pointer;
long *graphPointer = &GraphPtrOffset;
long *freeSpacePoint = &ok_FreeSpace;
int RSPNumber;
int RSPOffset;
char *hex = "0123456789ABCDEF";
//
//
