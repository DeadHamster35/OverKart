#include <stdbool.h>
#include "../library/SubProgram.h"
#include "../library/SharedFunctions.h"
#include "../library/OKHeader.h"
#include "../library/OKExternal.h"
#include "../library/LibraryVariables.h"
#include "../library/GameVariables/NTSC/OKassembly.h"
#include "../library/GameVariables/NTSC/GameOffsets.h"
#include "OverKartVariables.h"
#include "MarioKartPractice.h"
#include "MarioKartMenu.h"
#include "OKCustomObjects.h"
#include "CustomLevels.h"


void loadLogo()
{
	SetSegment(8,(int)(&ok_Logo));
	*sourceAddress = (int)(&LogoROM);
	*targetAddress = (int)(&ok_FreeSpace);
	dataLength = 0x3888;
	runDMA();
	*sourceAddress = (int)(&ok_FreeSpace);
	*targetAddress = (int)(&ok_Logo);
	runMIO();
	g_NintendoLogoOffset = 0x080059E8;
	g_NintendoLogoBorder = 0x256B9478;

}


void okSetup(void)
{
	loadHeaderOffsets();
	loadLogo();
	copyCourseTable(1);
	startupSwitch = 35;
	nopASM = 0;
	gameMode[0] = 1;
	renderMode[1] = 1;
	renderMode[2] = 1;
	HotSwapID = 0;
	asm_SongA = 0x240E0001;
	asm_SongB = 0x240E0001;
	asm_selectA = 0x2400;
	asm_selectC = 0x2400;
	asm_selectE = 0x2400;
	asm_selectB = 0x7FFF;
	asm_selectD = 0x7FFF;
	asm_selectF = 0x7FFF;
	hsGP = 0;
	FlyCamSpeed = 5;
	ok_Knowledge = (long)(&targetAddress);
}

bool checkEndGame()
{
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

	if (HotSwapID > 0)
	{
		runWaterVertex();
		loadMinimap();
		setWater();
		scrollLock = true;
		if ((gameMode[0] == 1) && (HotSwapID > 0))
		{
			GlobalAddressA = GetRealAddress(ok_RedCoinList);
			RedCoinChallenge(GlobalAddressA);
			CoinCount = 0;
		}

	}
}

void endRace()
{
	if (g_gameMode == 0x00)
	{
		if (checkEndGame())
		{
			scrollLock = false;
			g_loadedcourseFlag = 0xF0;
			gpTotalTime += g_TrialTime;
			gpCourseIndex++;
			if (HotSwapID > 0)
			{
				loadHotSwap(gpCourseIndex);
			}
		}
	}
}




void gameCode(void)
{





	printAnticheat();




	if (modMode[0] > 0 || modMode[1] > 0)
	{
		practiceHack();
	}
	if (modMode[2] > 0x00)
	{
		drawInputDisplay();
	}

	if (modMode[3] > 0x00)
	{
		printDetails();
	}

	if (CustomASM > 0x00)
	{
		ok_ASMJump();
	}


	if ((HotSwapID > 0) & (VersionNumber > 4))  //Version 5 Texture Scroll Function
	{
		if (scrollLock)
		{
			runTextureScroll();
		}
	}


	if ((HotSwapID > 0) || (renderMode[4] == 1))
	{
		g_farClip = 20000;
	}
	else
	{
		g_farClip = 6800;
	}

	if (g_startingIndicator == 0x03)
	{
		raceStatus = 0x03;
		DisplayCoinSprite();
	}
	if (g_startingIndicator == 0x02)
	{
		if (raceStatus != 0x02)
		{
			raceStatus = 0x02;
			startRace();
			hsLabel = -1;
		}
		if (g_gameMode == 0x00)
		{
			printGPTime(gpTotalTime);
			hsTableSet();
		}

		/*
		*sourceAddress = *(long*)(&ok_CourseHeader + 0xE);
		*targetAddress = (long)&ok_Credits;
		dataLength = 36;
		if ((HotSwapID > 0) && (*sourceAddress != 0x00000000))
		{
			runDMA();
			loadFont();
			GlobalIntA = *(long*)(&ok_Credits);
			if (GlobalIntA > 0)
			{
				printString( (140 - (GlobalIntA * 4)), 150, (char*)(&ok_Credits + 1));
			}

		}
		*/



	}
	if (g_startingIndicator == 0x05)
	{
		if (raceStatus != 0x05)
		{
			raceStatus = 0x05;
			endRace();
		}
		if (g_gameMode == 0x00)
		{
			printGPTime(gpTotalTime);
		}
	}



}
void resetMap()
{
	gpTotalTime = 0;
	gpCourseIndex = 0;
}



//
//
//
void allRun(void)
{

	if (startupSwitch != 35)
	{
		okSetup();
	}

	modCheck();


	if (gameMode[2] > 0x00)
	{
		asm_CupCount = 15;
	}
	else
	{
		asm_CupCount = 3;
	}






	if (SYSTEM_Region == 0x01)
	{

		if (g_InGame == 0x00)
		{

			if (p_Input > 0)
			{
				GenericInput = (short)p_Input;
			}
			else
			{
				GenericInput = (short)d_Input;
			}
			if (GenericInput == 0x00)
			{
				ButtonHeld = 0;   //set the boolean that tells us a button is held down to false
			}


			if (menuScreenA < 1)
			{
				HotSwapID = 0;

			}

			if ((menuScreenC >= 0x02) && (menuScreenA == 0x01) && (ButtonHeld == 0))
			{

				if (GenericInput == 0x20)  // L and Z, how convenient!
				{
					swapHS(0);
					ButtonHeld = 1;
				}
				if (GenericInput == 0x10)  // R!
				{
					swapHS(1);
					ButtonHeld = 1;
				}
				resetMap();

			}


			//

			//delete this soon
			// need more info on course tables and jumps

			if (HotSwapID > 0)
			{
				g_courseID = 0x00;

			}



			if (currentMenu == 0x24)
			{
				HotSwapID = 0;
				setPreviews();
				stockASM();
				hsLabel = -1;
			}
			if (currentMenu == 0x25)
			{
				switch(g_gameMode)
				{
					//GRAND PRIX

					case 0x00:
					{
						if (courseValue != (g_cupSelect * 4) + ((HotSwapID-1) * 0x10))
						{
							courseValue = (g_cupSelect * 4) + ((HotSwapID-1) * 0x10);
							loadHotSwap(0);
						}
						break;
					}
					default:
					{
						if (courseValue != (g_cupSelect * 4) + g_courseSelect + ((HotSwapID-1) * 0x10))
						{

							courseValue = (g_cupSelect * 4) + g_courseSelect + ((HotSwapID-1) * 0x10);
							loadHotSwap(0);
						}
						break;
					}
				}

				if (hsLabel != HotSwapID)
				{
					setLabel();
					hsLabel = HotSwapID;
				}
			}
			else
			{
				hsLabel = -1;
			}

		}
	}

}
