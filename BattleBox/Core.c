#include <stdbool.h>
#include "../library/GameVariables/NTSC/GameOffsets.h"
#include "../library/GameVariables/NTSC/OKHeader.h"
#include "../library/GameVariables/NTSC/OKassembly.h"
#include "MarioKartMenu.h"
#include "BattleBoxObject.h"
#include "../library/MarioKart3D.h"
#include "../library/SharedFunctions.h"
#include "../library/MarioKartObjects.h"



short hsLabel = 99;
short asmBool = 0;
short courseSwapped = 0;
short startupSwitch = 0;
int courseValue = 3000;
int raceStatus = 0; //used to mirror g_startingIndicator to ensure code runs once.
int battleStatus = 0;

//genericInput;





int gpCourseIndex = 0;

short genericInput = 0;
short buttonPressed = 0; //
int hsID = 0;
int hsGP = 0;
short gpTimeCheck = 0;

float gpTotalTime = 0;
float raceTime = 0;

int previewBuffer = 0x98D65D0;




void loadLogo()
{
	//left as example
	/*
	SetSegment(8,(int)(&ok_Logo));
	ok_Source = (int)(&LogoROM);
	ok_Target = (int)(&ok_FreeSpace);
	dataLength = 0x3888;
	runDMA();
	ok_Source = (int)(&ok_FreeSpace);
	ok_Target = (int)(&ok_Logo);
	runMIO();
	g_NintendoLogoOffset = 0x080059E8;
	g_NintendoLogoBorder = 0x256B9478;
	*/

}


void okSetup(void)
{
	//runs once at startup
	startupSwitch = 35;
	asm_BorderDraw = 0x2400;

}

bool CheckRaceResults()
{
	//returns true if the GP mode should advance (did the players win?)
	if (g_playerCount == 0x01)
	{
		if (g_playerPosition1 <= 3)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if ((g_playerPosition1 <= 3) || (g_playerPosition2 <= 3))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}



void startRace()
{
	switch(g_courseID)
	{
		case 0xF:
		{
			BoxCount = 36;
			break;
		}
		case 0x10:
		{
			BoxCount = 24;
			break;
		}
		case 0x11:
		{
			BoxCount = 42;
			break;
		}
		case 0x13:
		{
			BoxCount = 22;
			break;
		}
	}
	g_mapY = g_map2Y;
	g_map2Y = -32000;
	//runs at start of race

}

void endRace()
{

	//runs at end of race
}




void gameCode(void)
{
	//this code runs once every frame while rendering gameplay.
	battleStatus = 0;


	g_player1ScreenWidth = 320;
	g_player1ScreenHeight = 240;
	g_player1ScreenX = 160;
	g_player1ScreenY = 120;
	g_player2ScreenWidth = 2;
	g_player2ScreenHeight = 1;
	g_player2ScreenX = 330;
	g_player2ScreenY = 250;
	g_aspectRatio = 1.333333333333333;

	if ((g_gameTimer > raceTime) && (BoxCount > 0))
	{
		raceTime = g_gameTimer;
	}
	if (g_startingIndicator == 0x03)
	{
		raceStatus = 0x03;
	}
	if (g_startingIndicator == 0x02)
	{
		if (raceStatus != 0x02)
		{
			raceStatus = 0x02;
			startRace();
		}

	}
	if (g_startingIndicator == 0x05)
	{
		if (raceStatus != 0x05)
		{
			raceStatus = 0x05;
			endRace();
		}
	}
	loadFont();


	printStringNumber(80,190,"Item Boxes - ",BoxCount);
	printGPTime(gpTotalTime + raceTime);



}



//
//
//
void allRun(void)
{
	//this code runs once every frame all game.
	// it does NOT allow printing graphics or text.
	player2OK = 1;
	if (startupSwitch != 35)
	{
		okSetup();
	}
	if (currentMenu == 0x24)
	{
		BoxCount = 0;
		gpTotalTime = 0;
	}
	if (currentMenu == 0x25)
	{
		if (battleStatus == 0)
		{
			BoxCount = 0;
			battleStatus = 1;
			gpTotalTime += raceTime;
			raceTime = 0;
		}
	}


}

void MenuPrint()
{

	// this code will run during non-gameplay and allow for printing graphics/text.
}
