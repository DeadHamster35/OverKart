#include "../library/SubProgram.h"
#include "../library/SharedFunctions.h"
#include "../library/OKHeader.h"
#include "../library/OKExternal.h"
#include "../library/LibraryVariables.h"
#include "../library/GameVariables/NTSC/OKassembly.h"
#include "../library/GameVariables/NTSC/GameOffsets.h"
#include "../RawAssets/ModelData/ModelData.h"
#include "OverKartVariables.h"
#include "MarioKartMenu.h"
#include "MarioKartAI.h"

#include <stdbool.h>


//practiceHack Variables//
/*
char GlobalCharA;  //DpadInput
short GlobalCharD;  //Cpad Input
char GlobalCharB;   L/R Button
char GlobalCharC;   A/B Buttons
*/




char SplitTimerToggle, SplitTimerToggleSave = 0x00;
float SaveTimer, SplitTimer = 0;

static int SaveStateCourseID = 0x00;
short SplitStartMarker,SplitEndMarker = 0;
/*
static char itemSwap = 0x00;
static char resetToggle = 0x00;



*/

void splitFunc()
{
	if (SplitTimerToggle == 0x01)
	{
		if (g_progressValue < SplitStartMarker)
		{
			g_gameTimer = 0;
		}
		if (g_progressValue >= SplitStartMarker)
		{
			SplitTimerToggle = 0x02;
		}
	}
	if (SplitTimerToggle == 0x02)
	{
		if (g_progressValue >= SplitEndMarker)
		{
			SplitTimer = g_gameTimer;
			SplitTimerToggle = 0x03;
		}
	}
	if (SplitTimerToggle == 0x03)
	{
		g_gameTimer = SplitTimer;
	}

}




void modCheck()
{

	if (gameMode[1] > 0x00)
	{
			g_mirrorMode = 0x0001;
	}
	if (gameMode[3] > 0x00)
	{
		aiSetup();
	}
	//gameMode[4] handled in Menu

	if (renderMode[0] > 0x00)
	{
		if ((g_playerCount == 0x02) & (renderMode[3] == 0x00))
		{
			g_aspectRatio = 3.5;
		}
		else
		{
			g_aspectRatio = 1.77778;
		}
	}
	else
	{
		if (g_playerCount == 0x02)
		{
			g_aspectRatio = 2.6666667;
		}
		else
		{
			g_aspectRatio = 1.333334;
		}
	}
	if (renderMode[1] > 0x00)
	{
		antialiasToggle = 0x00013016;
		antialiasToggleB = 0x00013016;
	}
	//renderMode[2] 3D racers;
	if (renderMode[3] > 0x00)
	{
		if (g_playerCount == 0x02)
		{
			g_screenSplitA = 2;
			g_ScreenSplitB = 2;
		}
	}
	if (renderMode[5] > 0x00)
	{
		asm_tempo1A = 0x240F0000;
		asm_tempo1B = 0x240F0000;
		asm_tempo1ASpeed = 2;
		asm_tempo1BSpeed = 2;

		asm_tempo2A = 0x24090000;
		asm_tempo2B = 0x24090000;
		asm_tempo2ASpeed = 2;
		asm_tempo2BSpeed = 2;

		asm_tempo3A = 0x240A0000;
		asm_tempo3B = 0x240A0000;
		asm_tempo3ASpeed = 2;
		asm_tempo3BSpeed = 2;
	}




	//modMode[0] and modMode[2] handled in gameCode function.
	if (modMode[4] > 0x00)
	{
		if (modMode[4] < 0x09)
		{
			asm_itemJump1B = (0x84A5 | (itemChanceLo + 2));
			asm_itemJump2B = (0x84A5 | (itemChanceLo + 2));
			asm_itemJump1A = (0x3C05 | itemChanceHi);
			asm_itemJump2A = (0x3C05 | itemChanceHi);
			GlobalAddressA = (long)(&ok_ItemTable);
			for (int currentPlayer = 0; currentPlayer < 8; currentPlayer++)
			{
				*(long*)(&GlobalAddressA) = *(long*)(&g_playerPosition1 + currentPlayer);
				GlobalAddressA += 4;
			}
			for (int currentPlayer = 0; currentPlayer < g_playerCount; g_playerCount++)
			{
				*(long*)(&GlobalAddressA) = 8 - modMode[4];
				GlobalAddressA += 4;
			}
		}
	}
	else
	{
		asm_itemJump1B = 0x84A543BA;
		asm_itemJump2B = 0x84A543BA;
		asm_itemJump1A = 0x3C058016;
		asm_itemJump2A = 0x3C058016;
	}
}

void saveState()
{
	//simpleObjects
	dataLength = 0x2BC0;
	*targetAddress = (long)(&ok_SaveState);
	*sourceAddress = (long)(&g_SimpleObjectArray);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//dynamicObjects
	*targetAddress += dataLength;
	dataLength = 0x1E140;
	*sourceAddress = (long)(&g_DynamicObjects);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//playerData
	*targetAddress += dataLength;
	dataLength = 0x6EC0;
	*sourceAddress = (long)(&g_PlayerStateTable);
	ramCopy(*targetAddress, *sourceAddress, dataLength);


	//courseOBJ
	*targetAddress += dataLength;
	dataLength = 0x840;
	*sourceAddress = (long)(&g_CourseObstacle);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//camera data
	*targetAddress += dataLength;
	dataLength = 0x2E0;
	*sourceAddress = (long)(&g_CameraTable);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//lap timers
	*targetAddress += dataLength;
	dataLength = 0x210;
	*sourceAddress = (long)(&g_TimeLapTable);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//Player Timers
	*targetAddress += dataLength;
	dataLength = 0x20;
	*sourceAddress = (long)(&g_GameLapTable);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//Trials Time
	*targetAddress += dataLength;
	dataLength = 0x70;
	*sourceAddress = (long)(&g_TrialTime);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	SaveTimer = g_gameTimer;
	SplitTimerToggleSave = SplitTimerToggle;
}

void loadState()
{
	//simpleObjects
	dataLength = 0x2BC0;
	*sourceAddress = (long)(&ok_SaveState);
	*targetAddress = (long)(&g_SimpleObjectArray);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//dynamicObjects
	*sourceAddress += dataLength;
	dataLength = 0x1E140;
	*targetAddress = (long)(&g_DynamicObjects);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//playerData
	*sourceAddress += dataLength;
	dataLength = 0x6EC0;
	*targetAddress = (long)(&g_PlayerStateTable);
	ramCopy(*targetAddress, *sourceAddress, dataLength);


	//courseOBJ
	*sourceAddress += dataLength;
	dataLength = 0x840;
	*targetAddress = (long)(&g_CourseObstacle);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//camera data
	*sourceAddress += dataLength;
	dataLength = 0x2E0;
	*targetAddress = (long)(&g_CameraTable);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//lap timers
	*sourceAddress += dataLength;
	dataLength = 0x210;
	*targetAddress = (long)(&g_TimeLapTable);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//Player Timers
	*sourceAddress += dataLength;
	dataLength = 0x20;
	*targetAddress = (long)(&g_GameLapTable);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	//Trials Time
	*sourceAddress += dataLength;
	dataLength = 0x70;
	*targetAddress = (long)(&g_TrialTime);
	ramCopy(*targetAddress, *sourceAddress, dataLength);

	g_gameTimer = SaveTimer;
	SplitTimerToggle = SplitTimerToggleSave;
}



void drawInputDisplay()
{
	//static int 260 = 66, 215 = 32, w = 6, h = 6; //below lap counter


	GraphPtr = drawBox(GraphPtr,
	260, 215, 260+(8*7) +1, 215+(6*3) +1, //x1, y1, x2, y2
	0, 0, 0, 128); //r, g, b, a



	for(int i=0; i<16; i++)
	{
		if(names[i][0])
		{
			InputColor[0] = colors[i][0];
			InputColor[1] = colors[i][1];
			InputColor[2] = colors[i][2];

			if (p1Button & GlobalCharD)
			{
				InputColor[3] = 255;
			}
			else
			{
				InputColor[3] = 32;
			}
			AnalogInput[0] = 260 + (coords[i][0] * 8);
			AnalogInput[1] = 215 + (coords[i][1] * 6);

			GraphPtr = drawBox(GraphPtr,
				AnalogInput[0] + 1 , AnalogInput[1] + 1, AnalogInput[0]+8, AnalogInput[1]+6, //x1, y1, x2, y2
				InputColor[0], InputColor[1], InputColor[2], InputColor[3]); //r, g, b, a

		}
			GlobalCharD >>= 1;
	}
	for(int i=0; i<4; i++)
	{
		if(stickNames[i][0])
		{
			InputColor[0] = stickColor[i][0];
			InputColor[1] = stickColor[i][1];
			InputColor[2] = stickColor[i][2];

			if (p1Button & GlobalCharD)
			{
				InputColor[3] = 255;
			}
			else
			{
				InputColor[3] = 32;
			}
			AnalogInput[0] = 260 + (stickCoord[i][0] * 8);
			AnalogInput[1] = 215 + (stickCoord[i][1] * 6);

			GraphPtr = drawBox(GraphPtr,
				AnalogInput[0] + 1 , AnalogInput[1] + 1, AnalogInput[0]+8, AnalogInput[1]+6, //x1, y1, x2, y2
				InputColor[0], InputColor[1], InputColor[2], InputColor[3]); //r, g, b, a

		}
		GlobalCharD >>= 1;
	}


	InputColor[0] = stickColor[4][0];
	InputColor[1] = stickColor[4][1];
	InputColor[2] = stickColor[4][2];
	InputColor[3] = 255;
	AnalogInput[0] = 260 + ((stickCoord[4][0] * 8) + (player1inputX / 127.0f * 8));
	AnalogInput[1] = 215 + ((stickCoord[4][1] * 6) + (player1inputY / -127.0f * 6));

	GraphPtr = drawBox(GraphPtr,
		AnalogInput[0] + 1 , AnalogInput[1] + 1, AnalogInput[0]+8, AnalogInput[1]+6, //x1, y1, x2, y2
		InputColor[0], InputColor[1], InputColor[2], InputColor[3]); //r, g, b, a

}



void rotateCamera(int inputAngle)
{

	FlyCamAngle = ((float)inputAngle / 360.0) * 65535.0;
	objectAngle[0] = (short)FlyCamAngle;
	FlyCamLook[0][0] = g_player1LocationX - g_player1CameraX;
	FlyCamLook[1][0] = g_player1LocationZ - g_player1CameraZ;

	FlyCamLook[0][1] = FlyCamLook[0][0] * cosF(FlyCamAngle) - FlyCamLook[1][0] * sinF(FlyCamAngle);
	FlyCamLook[1][1] = FlyCamLook[0][0] * sinF(FlyCamAngle) + FlyCamLook[1][0] * cosF(FlyCamAngle);

	g_player1LocationX = FlyCamLook[0][1] + g_player1CameraX;
	g_player1LocationZ = FlyCamLook[1][1] + g_player1CameraZ;
	g_player1LocationA = g_player1LocationA + objectAngle[0];
}


void moveCamera(int inputDistance)
{
	FlyCamAngle = (((float)g_player1LocationA / 65535) * 360);
	FlyCamRadian = (int)FlyCamAngle * -0.0174533;
	g_player1LocationX = (float)(g_player1LocationX + inputDistance * sinF(FlyCamRadian));
	g_player1LocationZ = (float)(g_player1LocationZ + inputDistance * cosF(FlyCamRadian));
}

void moveCameraTilt(int inputDistance, int tilt)
{
	FlyCamAngle = (((float)g_player1LocationA / 65535) * 360) + tilt;
	if (tilt > 0)
	{
		if (FlyCamAngle > 360)
		FlyCamAngle -= 360;
	}
	else
	{
		if (FlyCamAngle < 0)
		FlyCamAngle += 360;
	}


	FlyCamRadian = (int)FlyCamAngle * -0.0174533;
	g_player1LocationX = (float)(g_player1LocationX + inputDistance * sinF(FlyCamRadian));
	g_player1LocationZ = (float)(g_player1LocationZ + inputDistance * cosF(FlyCamRadian));
}

//modmode[0] is > 0 then
void practiceHack()
{
	GlobalCharA = (d_Input & 0x0F);	 //Dpad
	GlobalCharB = (p_Input & 0xF0);  //LR Trigger
	GlobalCharC = (d_Input & 0xF0);  //AB Button
	GlobalCharD = (p_Input & 0x0F);  //Cpad
	if (modMode[0] == 1)
	{
		
		if (SplitTimerToggle > 0x00)
		{
			splitFunc();

		}
		if (GlobalCharA == 0x00)
		{
			ButtonHeld = 0x00;
		}
		// D-Pad Hacks.
		if (GlobalCharD == 0x02)
		{
			g_player1LocationY = g_player1LocationY + 3;
			g_player1SpeedY = 0;
			GraphPtr = drawBox(GraphPtr, 23, 43, 120, 53, 0, 0,0, 175);
	          loadFont();
	          printString(5,25, "FLYING");
		}
		if (ButtonHeld == 0x00)
		{
			if (GlobalCharB == 0x20)
			{
				switch(GlobalCharA)
				{

					// End Split hack.
					case 0x01 :
					{

						ButtonHeld = 1;
						SplitEndMarker = g_progressValue;

						break;
					}

					//Start Split hack.
					case 0x02 :
					{

						ButtonHeld = 1;
						SplitStartMarker = g_progressValue;
						break;
					}

					// Turn Off Split Timer
					case 0x04 :
					{
						SplitTimerToggle = 0x00;

						ButtonHeld = 1;
						break;
					}

					// Turn on Split Timer
					case 0x08 :
					{
						SplitTimerToggle = 0x01;

						break;
					}
				}
			}
			else
			{
				switch(GlobalCharA)
				{

					// Load Position hack.
					case 0x01 :
					{
						if (SaveStateCourseID == ((HotSwapID * 0x10) + g_courseID + 1))
						{
							ButtonHeld = 1;
							loadState();
						}
						break;
					}

					// Save Position hack.

					case 0x02 :
					{

						ButtonHeld = 1;
						SaveStateCourseID = ((HotSwapID * 0x10) + g_courseID + 1);
						saveState();
						break;
					}

					// Reset Timer and Lap Hack
					case 0x04 :
					{
						g_gameLapPlayer1 = 0x00;
						g_lapCheckA = 0x00;
						g_lapCheckB = 0x00;

						g_gameTimer = 90;
						//GIVE PLAYER TRIPLE MUSHROOM

						ButtonHeld = 1;
						break;
					}

					//FASTRESET Hack
					case 0x08 :
					{
						
						g_resetToggle = 0x01;
						ButtonHeld = 1;

						break;
					}
				}
			}
		}
	}


	if (modMode[1] == 1)
	{
		asm_DisableEngineSound = 0x0100;
		asm_DisableHUD = 0x2400;
		g_GhostHUDID = 0;
		g_playerSpriteSize = 0;
		g_playerStatus = 0;
		if ((FlyCamPosition[0] == 0) && (FlyCamPosition[1] == 0))
		{
			FlyCamPosition[0] = g_player1LocationX;
			FlyCamPosition[1] = g_player1LocationY;
			FlyCamPosition[2] = g_player1LocationZ;
		}
		else
		{
			g_player1LocationX = FlyCamPosition[0];
			g_player1LocationY = FlyCamPosition[1];
			g_player1LocationZ = FlyCamPosition[2];
		}


		if ((c_Input == 0) && (GlobalCharC == 0) && (GlobalCharD == 0) && (GlobalCharA == 0))
		{
			ButtonHeld = 0x00;
		}


		if (ButtonHeld == 0x00)
		{	
			switch(GlobalCharC)
			{
				case 0x04:
				{
					moveCamera((int)(-1 * FlyCamSpeed));
					break;
				}
				case 0x08:
				{
					moveCamera(FlyCamSpeed);
					break;
				}
			}
			

			if (GlobalCharB == 0x10)
			{
				GraphPtr = drawBox(GraphPtr, 23, 43, 120, 63, 0, 0,0, 175);
				loadFont();
				printStringNumber(5,25, "SECTION-", g_player1Section);
				printStringNumber(5,35, "SPEED-", FlyCamSpeed);

				if ((c_Input & 0x01) == 0x01)
				{
					moveCameraTilt(FlyCamSpeed,90);
				}
				if ((c_Input & 0x02) == 0x02)
				{
					moveCameraTilt(FlyCamSpeed,-90);
				}
				if ((c_Input & 0x04) == 0x04)
				{
					g_player1LocationY = g_player1LocationY - FlyCamSpeed * .6;
				}
				if ((c_Input & 0x08) == 0x08)
				{
					g_player1LocationY = g_player1LocationY + FlyCamSpeed * .6;
				}
				switch(GlobalCharA)
				{

					case 0x01:
					{
						g_player1Section = g_player1Section + 1;
						ButtonHeld = 1;
						break;
					}
					case 0x02:
					{
						if (g_player1Section > 1)
						{
							g_player1Section = g_player1Section - 1;
						}
						ButtonHeld = 1;
						break;
					}
					case 0x04 :
					{
						if (FlyCamSpeed > 5)
						{
							FlyCamSpeed = FlyCamSpeed - 5;
						}
						else
						{
							if (FlyCamSpeed > 1)
							{
								FlyCamSpeed = FlyCamSpeed - 1;
							}
						}
						
						ButtonHeld = 1;
						break;
					}

					// Turn on Split Timer
					case 0x08 :
					{
						if (FlyCamSpeed < 5)
						{
							FlyCamSpeed = FlyCamSpeed + 1;
						}
						else
						{							
							FlyCamSpeed = FlyCamSpeed + 5;							
						}
						ButtonHeld = 1;
						break;
					}
				}
			}
			else
			{
				switch(GlobalCharD)
				{
					case 0x01:
					{
						moveCameraTilt(FlyCamSpeed,90);
						break;
					}
					case 0x02:
					{
						moveCameraTilt(FlyCamSpeed,-90);
						break;
					}
				}
				if ((c_Input & 0x01) == 0x01)
				{
					rotateCamera(5);
				}
				if ((c_Input & 0x02) == 0x02)
				{
					rotateCamera(-5);
				}
				if ((c_Input & 0x04) == 0x04)
				{
					g_player1LocationY = g_player1LocationY - FlyCamSpeed * .6;
				}
				if ((c_Input & 0x08) == 0x08)
				{
					g_player1LocationY = g_player1LocationY + FlyCamSpeed * .6;
				}
			}

		}


		FlyCamPosition[0] = g_player1LocationX;
		FlyCamPosition[1] = g_player1LocationY;
		FlyCamPosition[2] = g_player1LocationZ;

	}






	//devmode

	if (modMode[0] == 2)
	{
		printMap(MapMode);
		if (GlobalCharA == 0x00)
		{
			ButtonHeld = 0x00;
		}
		if (GlobalCharB == 0x10)
		{

			switch(GlobalCharA)
			{
				case 0x08 :
				{
					if (MapMode > 0 && ButtonHeld == 0)
					{
						MapMode--;
						ButtonHeld = 1;
					}
					break;
				}

				case 0x04 :
				{
					if (MapMode < 3 && ButtonHeld == 0)
					{
						MapMode++;
						ButtonHeld = 1;
					}
					break;
				}
			}
		}
		else
		{
			ButtonHeld = 0;
			switch(MapMode)
			{
				case 0:
				{
					//map

					switch(GlobalCharA)
					{

						case 0x01 :
						{
							g_mapX++;
							break;
						}


						case 0x02 :
						{

							g_mapX--;
							break;
						}

						case 0x04 :
						{
							g_mapY++;
							break;
						}

						case 0x08 :
						{
							g_mapY--;
							break;
						}
					}
					break;
				}



				case 1:
				{
					//map
					switch(GlobalCharA)
					{

						case 0x01 :
						{
							g_startX++;
							break;
						}


						case 0x02 :
						{

							g_startX--;
							break;
						}

						case 0x04 :
						{
							g_startY++;
							break;
						}

						case 0x08 :
						{
							g_startY--;
							break;
						}
					}
					break;
				}



				case 2:
				{
					//map
					switch(GlobalCharA)
					{

						case 0x01 :
						{
							g_mapScale = g_mapScale + .0001;
							break;
						}


						case 0x02 :
						{

							g_mapScale = g_mapScale - .0001;
							break;
						}
					}
					break;
				}

			}
		}
	}

}
