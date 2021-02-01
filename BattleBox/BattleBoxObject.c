#include <stdbool.h>
#include "../library/SubProgram.h"
#include "../library/GameVariables/NTSC/GameOffsets.h"
#include "../library/SharedFunctions.h"

int BoxCount = 0;

void DisplayObject(void *Camera, void *Object)
{
	int objectID = (short)((*(long*)(*(long*)(&Object)) >> 16) & 0x0000FFFF);

	objectID = objectID - 2;//alligns ID with original jump routine.
	switch (objectID)
	{
		case 45:
		{
			//DisplayRedCoin(Camera,Object);
			break;
		}
		default:
		{
			break;
		}
	}



}



int BoxDestroy(void *Car, void *Box)
{
	if ((CollisionSphere(Car,Box) == 1))
	{
		int playerID = (*(long*)&Car - (long)&g_PlayerStateTable) / 0xDD8;
		deleteObjectBuffer(Box);
		playSound(0x49008017);
		RouletteStart(playerID,0);
		BoxCount--;
	}
	return(0);
}

void CollideObject(void *Car, void *Object)
{
	int objectID = (short)((*(long*)(*(long*)(&Object)) >> 16) & 0x0000FFFF);

	switch (objectID)
	{
		case 12:
		{
			BoxDestroy(Car,Object);

			break;
		}
		default:
		{
			break;
		}
	}
}
