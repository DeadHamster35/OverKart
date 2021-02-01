#include "../library/SubProgram.h"
#include "../library/SharedFunctions.h"
#include "../library/OKHeader.h"
#include "../library/LibraryVariables.h"
#include "../library/GameVariables/NTSC/OKassembly.h"
#include "../library/GameVariables/NTSC/GameOffsets.h"
#include "OverKartVariables.h"

/*
char GlobalCharA; CPU STY
char GlobalCharB; FORCE CPU
char GlobalCharC; START BOOST
*/
void fastAI()
{
     switch(g_raceClass)
     {
          case 0x00:
          {
               GlobalFloatA = 498.0;
               break;
          }
          case 0x01:
          {
               GlobalFloatA = 518.0;
               break;
          }
          case 0x02:
          {
               GlobalFloatA = 530.0;
               break;
          }
     }

     if ((g_startingIndicator < 0x03) && (GlobalCharC == 0x00))
     {
          GlobalCharC = 0x01;
     }
     if ((g_startingIndicator == 0x03) && (GlobalCharC == 0x01))
     {
          GlobalCharC = 0x00;
          switch(g_playerCount)
          {
               case 0x01 :
               {
                    boost2 = 0x02;
                    boost3 = 0x02;
                    boost4 = 0x02;
                    break;
               }
               case 0x02 :
               {
                    boost2 = 0x02;
                    break;
               }
               case 0x03 :
               {
                    boost2 = 0x02;
                    boost3 = 0x02;
                    break;
               }
               case 0x04 :
               {
                    boost2 = 0x02;
                    boost3 = 0x02;
                    boost4 = 0x02;
                    break;
               }
          }
     }
     if (g_gameTimer > 5.0)
     {
          switch(g_playerCount)
          {
               case 0x01 :
               {
                    cpu2Speed = GlobalFloatA;
                    cpu3Speed = GlobalFloatA;
                    cpu4Speed = GlobalFloatA;

                    break;
               }
               case 0x02 :
               {
                    cpu2Speed = GlobalFloatA;

                    break;
               }
               case 0x03 :
               {
                    cpu2Speed = GlobalFloatA;
                    cpu3Speed = GlobalFloatA;

                    break;
               }
               case 0x04 :
               {
                    cpu2Speed = GlobalFloatA;
                    cpu3Speed = GlobalFloatA;
                    cpu4Speed = GlobalFloatA;

                    break;
               }
          }

     }
}




void checkAI()
{
     if (GlobalCharB > 0x00)
	{
		switch (gameMode[3])
		{
			case 0x01 :
			{
				GlobalCharA = 0x91;
				break;
			}
			case 0x02 :
			{
				GlobalCharA = 0xD1;
				break;
			}
		}


		switch(g_playerCount)
		{
			case 0x01 :
			{
				g_player1State = GlobalCharA;
				g_player2State = GlobalCharA;
				g_player3State = GlobalCharA;

				break;
			}
			case 0x02 :
			{
				g_player1State = GlobalCharA;

				break;
			}
			case 0x03 :
			{
				g_player1State = GlobalCharA;
				g_player2State = GlobalCharA;

				break;
			}
			case 0x04 :
			{
				g_player1State = GlobalCharA;
				g_player2State = GlobalCharA;
				g_player3State = GlobalCharA;

				break;
			}
		}

	}




}



void aiSetup()
{
     if (gameMode[3] > 0x00)
	{
		player2OK = 0X01;
		player3OK = 0x01;
		player4OK = 0x01;
	}
	else
	{

	}



	if ((gameMode[3] > 0x00) && (g_startingIndicator >= 0x02))
	{
		GlobalCharB = 0x01;
	}
	if ((g_loadedcourseFlag == 0xFF) || (g_startingIndicator < 0x02))
	{
		GlobalCharB = 0x00;
	}

     if (gameMode[3] == 0x02)
     {
          fastAI();
     }

     checkAI();

     //
}
