#include "../library/SubProgram.h"
#include "../library/SharedFunctions.h"
#include "../library/OKHeader.h"
#include "../library/OKExternal.h"
#include "../library/LibraryVariables.h"
#include "../library/MarioKartObjects.h"
#include "../library/MarioKart3D.h"
#include "../library/GameVariables/NTSC/OKassembly.h"
#include "../library/GameVariables/NTSC/GameOffsets.h"
#include "../RawAssets/ModelData/ModelData.h"
#include "OverKartVariables.h"

/*
81020000 03E0
81020002 0008
81020004 2400
81021244 03E0
81021246 0008
81021248 2400*/




void Draw3DRacer()
{
	/*
	if (renderMode[2] == 0)
	{
		spriteKillA = 0x27BDFFA0;
		spriteKillB = 0xAFBF;
		spriteKillC = 0x27BDFFE8;
		spriteKillD = 0xAFBF;
	}
	else
	{
		
		spriteKillA = 0x03E00008;
		spriteKillB = 0x2400;
		spriteKillC = 0x03E00008;
		spriteKillD = 0x2400;
		




		GlobalAddressB = (long)&bowserLOD0;
		GlobalAddressA = (long)(&g_PlayerStateTable);

		baseTurn = *(short*)(GlobalAddressA + 46);
		addTurn = *(short*)(GlobalAddressA + 192);

		objectPosition[0] = *(float*)(GlobalAddressA + 20);
		objectPosition[1] = *(float*)(GlobalAddressA + 24) - 5;
		objectPosition[2] = *(float*)(GlobalAddressA + 28);
		objectAngle[2] = baseTurn + addTurn;
		objectAngle[0] = 0x3FFF - *(short*)(GlobalAddressA + 518) * 2;
		objectAngle[1] = *(short*)(GlobalAddressA + 80) * -2;

		DrawGeometryScale(objectPosition,objectAngle,GlobalAddressB, 0.08);
	}

	*/
}



void DisplayRedCoin(void *Camera, void *Object)
{
	//camera goes unused but is passed by the game's internal function

	GlobalAddressA = *(long*)(&Object);
	GlobalAddressB = (long)&RedCoin;
	//fuccck
	//UpdateObjectVelocity(Object);
	objectPosition[0] = *(float*)(GlobalAddressA + 24);
	objectPosition[1] = *(float*)(GlobalAddressA + 28);
	objectPosition[2] = *(float*)(GlobalAddressA + 32);

	objectAngle[0] = *(short*)(GlobalAddressA + 16);
	objectAngle[1] = *(short*)(GlobalAddressA + 18);
	objectAngle[2] = *(short*)(GlobalAddressA + 20);
	*(short*)(GlobalAddressA + 18) += DEG1 * 3;


	DrawGeometryScale(objectPosition,objectAngle,GlobalAddressB, 0.10);
}



int RedCoinCollide(void *Car, void *Coin)
{
	GlobalAddressA = *(long*)(&Coin);
	objectPosition[0] = *(float*)(GlobalAddressA + 24);
	objectPosition[1] = *(float*)(GlobalAddressA + 28);
	objectPosition[2] = *(float*)(GlobalAddressA + 32);
	if ((CollisionCylinder(Car,objectPosition,3.0f,5.0f,0.0f) == 1))
	{
		*targetAddress = 0x353500FF;
		deleteObjectBuffer(Coin);
		playSound(0x49008017);
		CoinCount++;
	}
	if (CoinCount == 8)
	{
		int playerID = (*(long*)&Car - (long)&g_PlayerStateTable) / 0xDD8;
		SetStar(Car,playerID);
		CoinCount++;
	}

	return(0);
}


void DisplayCoinSprite()
{
	for(int currentSprite = 1; (currentSprite <= CoinCount) & (currentSprite <= 8); currentSprite++)
	{
		KWSprite((currentSprite* 16) + 10,220,16,16,(short*)&ok_RedCoinSprite);
	}
}



void CollideObject(void *Camera, void *Object)
{
	objectIndex = (short)((*(long*)(*(long*)(&Object)) >> 16) & 0x0000FFFF);
	switch (objectIndex)
	{
		case 47:
		{
			RedCoinCollide(Camera,Object);

			break;
		}
		default:
		{
			break;
		}
	}
}

void DisplayObject(void *Camera, void *Object)
{
	objectIndex = (short)((*(long*)(*(long*)(&Object)) >> 16) & 0x0000FFFF);

	switch (objectIndex)
	{
		case 47:
		{
			DisplayRedCoin(Camera,Object);

			break;
		}
		default:
		{
			break;
		}
	}
}


void loadCoin()
{
	SetSegment(8,(int)(&ok_ModelData));
	*sourceAddress = (int)(&ModelDataStart);
	*targetAddress = (int)(&ok_FreeSpace);
	dataLength = (int)ModelData_CompressedSize;
	runDMA();
	*sourceAddress = (int)(&ok_FreeSpace);
	*targetAddress = (int)(&ok_ModelData);
	runMIO();
	//
	//
	*sourceAddress = (int)(&RCSpriteROM);
	*targetAddress = (int)(&ok_FreeSpace);
	dataLength = 0x204;
	runDMA();
	*sourceAddress = (int)(&ok_FreeSpace);
	*targetAddress = (int)(&ok_RedCoinSprite);
	runMIO();
}



void RedCoinChallenge(long PathOffset)
{
	*tempPointer = PathOffset;
	*sourceAddress = (long)&CoinPositions;
	*targetAddress = (long)&objectPosition;
	for (int currentCoin = 0; currentCoin < 8; currentCoin++)
	{		
		CoinPositions[currentCoin][0] = *(short*)(PathOffset);
		CoinPositions[currentCoin][1] = *(short*)(PathOffset + 2);
		CoinPositions[currentCoin][2] = *(short*)(PathOffset + 4);
		
		if (CoinPositions[currentCoin][0] == 0xFFFF8000)
		{
			if (currentCoin < 7)
			{
				return; //if there's not 8 coins don't run the function.
			}
			else
			{
				break;
			}
		}
		PathOffset = PathOffset + 8;
	}

	//two loops for above return; ensure 8 coins.

	for (int currentCoin = 0; currentCoin < 8; currentCoin++)
	{
		objectPosition[0] = (float)CoinPositions[currentCoin][0];		
		objectPosition[1] = (float)CoinPositions[currentCoin][1];
		objectPosition[2] = (float)CoinPositions[currentCoin][2];
		CreateObject(objectPosition,47);
	}


}
