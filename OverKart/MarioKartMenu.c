#include <stdbool.h>
#include <math.h>
#include "../library/SubProgram.h"
#include "../library/SharedFunctions.h"
#include "../library/OKHeader.h"
#include "../library/LibraryVariables.h"
#include "../library/GameVariables/NTSC/OKassembly.h"
#include "../library/GameVariables/NTSC/GameOffsets.h"
#include "../library/MarioKartObjects.h"
#include "../library/MarioKartStats.h"
#include "MarioKartAI.h"
#include "../RawAssets/ModelData/ModelData.h"
#include "OverKartVariables.h"
#include "CustomLevels.h"
#include "OKCustomObjects.h"
#include "MarioKartPractice.h"





void loadPosition()
{
     switch(g_playerCount)
     {
          case 0x01 :
          {
               MenuPosition[0] = 5;
               MenuPosition[1] = 15;
               break;
          }
          case 0x02 :
          {
               MenuPosition[0] = 90;
               MenuPosition[1] = 97;
               break;
          }
          case 0x03 :
          {
               MenuPosition[0] = 170;
               MenuPosition[1] = 200;
               break;
          }
          case 0x04 :
          {
               MenuPosition[0] = 90;
               MenuPosition[1] = 97;
               break;
          }
     }
}



void PrintMenuTest()
{

}

void printGPTime(float printTime)
{




     wholeNumber = (int) printTime;
     decimalNumber = (int) ((printTime - wholeNumber) * 100);



     if (decimalNumber < 0)
     {
          decimalNumber = decimalNumber * -1;
     }

     if (wholeNumber > 60)
     {
          minutes = (long)(floor)(wholeNumber/60);
          seconds = wholeNumber - (minutes * 60);
     }
     else
     {
          seconds = wholeNumber;
     }

     if (minutes >= 10)
     {
          if (minutes >= 100)
          {
               if (minutes >= 1000)
               {

                    printOffsetA = 40;
               }
               else
               {
                    printOffsetA = 32;
               }
          }
          else
          {
               printOffsetA = 24;
          }
     }
     else
     {
          printOffsetA = 16;
     }

     if (seconds >= 10)
     {
          if (seconds >= 100)
          {
               if (seconds >= 1000)
               {

                    printOffsetB = 40;
               }
               else
               {
                    printOffsetB = 32;
               }
          }
          else
          {
               printOffsetB = 24;
          }
     }
     else
     {
          printOffsetB = 16;
     }



     printOffsetB = printOffsetB + printOffsetA;


     loadFont();
     MenuPosition[1] = 210;
     MenuPosition[0] = 55;

     printString(MenuPosition[0],MenuPosition[1],"Total Time:");

     MenuPosition[0] = 145;


     printString(MenuPosition[0] + printOffsetA, MenuPosition[1], "'");
     if (seconds < 10)
     {
          printStringNumber(MenuPosition[0] + printOffsetA,MenuPosition[1],"",0);
          printOffsetA = printOffsetA + 8;
          printOffsetB = printOffsetB + 8;
     }

     printString(MenuPosition[0] + printOffsetB, MenuPosition[1], "\"");
     if (decimalNumber < 10)
     {
          printStringNumber(MenuPosition[0]+printOffsetB,MenuPosition[1],"",0);
          printOffsetB = printOffsetB + 8;
     }




     printStringNumber(MenuPosition[0],MenuPosition[1],"",minutes);
     printStringNumber(MenuPosition[0] + printOffsetA,MenuPosition[1],"",seconds);
     printStringNumber(MenuPosition[0]+printOffsetB,MenuPosition[1],"",decimalNumber);



}

void printFloat(float printTime)
{



     wholeNumber = (int) printTime;
     decimalNumber = (int) ((printTime - wholeNumber) * 100);


     if (decimalNumber < 0)
     {
          decimalNumber = decimalNumber * -1;
     }

     if (wholeNumber >= 10)
     {
          if (wholeNumber >= 100)
          {
               if (wholeNumber >= 1000)
               {

                    printOffsetA = 48;
               }
               else
               {
                    printOffsetA = 40;
               }
          }
          else
          {
               printOffsetA = 32;
          }
     }
     else
     {
          printOffsetA = 24;
     }




     loadFont();
     MenuPosition[1] = 210;
     MenuPosition[0] = 55;

     printString(MenuPosition[0],MenuPosition[1],"Height:");

     MenuPosition[0] = 145;


     printString(MenuPosition[0] + printOffsetA, MenuPosition[1], ".");
     printOffsetA = printOffsetA + 8;
     if (decimalNumber < 10)
     {
          printStringNumber(MenuPosition[0]+printOffsetA,MenuPosition[1],"",0);
          printOffsetA = printOffsetA + 8;
     }




     printStringNumber(MenuPosition[0],MenuPosition[1],"",wholeNumber);
     printStringNumber(MenuPosition[0]+printOffsetA,MenuPosition[1],"",decimalNumber);



}


void printMap(char devParameter)
{
          if (g_playerCount == 1)
          {
               MenuPosition[0] = 25;
               MenuPosition[1] = 150;
               GraphPtr = drawBox(GraphPtr, MenuPosition[0] + 18, MenuPosition[1] + 18, MenuPosition[0] + 185, MenuPosition[1] + 68, 0, 0, 0, 175);
               GraphPtr = drawBox(GraphPtr, MenuPosition[0] + 18, MenuPosition[1] + 18 + (devParameter * 20), MenuPosition[0] + 74, MenuPosition[1] + 28 + (devParameter * 20), 200, 0, 0, 175);
               loadFont();


               printStringNumber(MenuPosition[0],MenuPosition[1],"  Map X:",g_mapX);
               printStringNumber(MenuPosition[0],MenuPosition[1]+10,"  Map Y:",g_mapY);
               printStringNumber(MenuPosition[0],MenuPosition[1]+20,"Start X:",g_startX);
               printStringNumber(MenuPosition[0],MenuPosition[1]+30,"Start Y:",g_startY);
               printString(MenuPosition[0],MenuPosition[1]+40,"  Scale:");

               wholeNumber = (int) (g_mapScale * 100);
               decimalNumber = (int) (((g_mapScale * 100) - wholeNumber) * 1000);

               if (decimalNumber < 0)
               {
                    decimalNumber = decimalNumber * -1;
               }
               if (wholeNumber >= 10)
               {
                    if (wholeNumber >= 100)
                    {
                         if (wholeNumber >= 1000)
                         {

                              printOffsetB = 8;
                         }
                         else
                         {
                         printOffsetB = 16;
                         }
                    }
                    else
                    {
                    printOffsetB = 24;
                    }
               }
               else
               {
                    printOffsetB = 32;
               }
               if (wholeNumber >= 0)
               {
                    printOffsetB = printOffsetB + 8;
               }

               printOffsetA = 56;

               if (decimalNumber < 100)
               {
                    printStringNumber(MenuPosition[0]+printOffsetA-4,MenuPosition[1]+ 40,"",0);
                    printOffsetC = 8;
               }
               else
               {
                    printOffsetC = 0;
               }
               MenuPosition[0] = 50;

               printStringNumber(MenuPosition[0]+printOffsetB,MenuPosition[1] + 40,"",wholeNumber);
               printString(MenuPosition[0]+printOffsetA,MenuPosition[1] + 40,".");
               printStringNumber(MenuPosition[0]+printOffsetA-4+printOffsetC,MenuPosition[1] + 40,"",decimalNumber);


     }

}


void printDetails()
{
     if (g_playerCount == 1)
     {
          MenuPosition[0] = 58;
          MenuPosition[1] = 170;
          GraphPtr = drawBox(GraphPtr, MenuPosition[0] + 18, MenuPosition[1] + 18, MenuPosition[0] + 185, MenuPosition[1] + 58, 0, 0, 0, 175);
          loadFont();


          printString(MenuPosition[0],MenuPosition[1],"X:");
          printString(MenuPosition[0],MenuPosition[1]+10,"Y:");
          printString(MenuPosition[0],MenuPosition[1]+20,"Z:");
          printString(MenuPosition[0],MenuPosition[1]+30,"A:");

          if (modMode[3] == 1)
          {
               printString(MenuPosition[0]+87,MenuPosition[1]," SX:");
               printString(MenuPosition[0]+87,MenuPosition[1]+10," SY:");
               printString(MenuPosition[0]+87,MenuPosition[1]+20," SZ:");
          }
          else
          {
               printString(MenuPosition[0]+87,MenuPosition[1]," LA:");
               printString(MenuPosition[0]+87,MenuPosition[1]+10," LS:");
               printString(MenuPosition[0]+87,MenuPosition[1]+20," PG:");
          }


          printString(MenuPosition[0]+87,MenuPosition[1]+30," SA:");


          for(int loop = 0; loop < 4; loop++)
          {
               switch  (loop)
               {
                    case 0x00:
                    {
                         wholeNumber = (int) g_player1LocationX;
                         decimalNumber = (int) ((g_player1LocationX - wholeNumber) * 1000);
                         break;
                    }
                    case 0x01:
                    {
                         wholeNumber = (int) g_player1LocationY;
                         decimalNumber = (int) ((g_player1LocationY - wholeNumber) * 1000);
                         break;
                    }
                    case 0x02:
                    {
                         wholeNumber = (int) g_player1LocationZ;
                         decimalNumber = (int) ((g_player1LocationZ - wholeNumber) * 1000);
                         break;
                    }
                    case 0x03:
                    {
                         float playerAngle = (((float)g_player1LocationA / 65536) * 360);
                         wholeNumber = playerAngle;
                         decimalNumber = (int) ((playerAngle - wholeNumber) * 1000);
                         break;
                    }

               }
               if (decimalNumber < 0)
               {
                    decimalNumber = decimalNumber * -1;
               }

               if (wholeNumber > 0)
               {
                    printOffsetD = wholeNumber;
               }
               else
               {
                    printOffsetD = wholeNumber * -1;
               }
               if (printOffsetD >= 10)
               {
                    if (printOffsetD >= 100)
                    {
                         if (printOffsetD >= 1000)
                         {

                              printOffsetB = 8;
                         }
                         else
                         {
                         printOffsetB = 16;
                         }
                    }
                    else
                    {
                    printOffsetB = 24;
                    }
               }
               else
               {
                    printOffsetB = 32;
               }
               if (wholeNumber >= 0)
               {
                    printOffsetB = printOffsetB + 8;
               }

               printOffsetA = 56;

               if (decimalNumber < 100)
               {
                    printStringNumber(MenuPosition[0]+printOffsetA-4,MenuPosition[1],"",0);
                    printOffsetC = 8;
               }
               else
               {
                    printOffsetC = 0;
               }



               printStringNumber(MenuPosition[0]+printOffsetB,MenuPosition[1],"",wholeNumber);
               printString(MenuPosition[0]+printOffsetA,MenuPosition[1],".");
               printStringNumber(MenuPosition[0]+printOffsetA-4+printOffsetC,MenuPosition[1],"",decimalNumber);
               MenuPosition[1] = MenuPosition[1] + 10;
               //
               //
          }


          MenuPosition[0] = MenuPosition[0] + 87;
          MenuPosition[1] = 170;
          for(int loop = 0; loop < 4; loop++)
          {
               switch  (loop)
               {
                    case 0x00:
                    {
                         if (modMode[3] == 1)
                         {
                              wholeNumber = (int) g_player1SpeedX;
                              decimalNumber = (int) ((g_player1SpeedX - wholeNumber) * 1000);
                         }
                         else
                         {
                              wholeNumber = (int) g_lakituSurface;
                         }

                         break;
                    }
                    case 0x01:
                    {
                         if (modMode[3] == 1)
                         {
                              wholeNumber = (int) g_player1SpeedY;
                              decimalNumber = (int) ((g_player1SpeedY - wholeNumber) * 1000);
                         }
                         else
                         {
                              wholeNumber = (int) g_lakituStatus;
                         }

                         break;
                    }
                    case 0x02:
                    {
                         if (modMode[3] == 1)
                         {
                              wholeNumber = (int) g_player1SpeedZ;
                              decimalNumber = (int) ((g_player1SpeedZ - wholeNumber) * 1000);
                         }
                         else
                         {
                              wholeNumber = (int) g_progressValue;
                         }

                         break;
                    }
                    case 0x03:
                    {
                         wholeNumber = (int) g_player1SpeedA;
                         decimalNumber = (int) ((g_player1SpeedA - wholeNumber) * 1000);
                         break;
                    }
               }
               if (decimalNumber < 0)
               {
                    decimalNumber = decimalNumber * -1;
               }


               if (wholeNumber > 0)
               {
                    printOffsetD = wholeNumber;
               }
               else
               {
                    printOffsetD = wholeNumber * -1;
               }
               if (printOffsetD >= 10)
               {
                    if (printOffsetD >= 100)
                    {
                         printOffsetB = 8;
                    }
                    else
                    {
                    printOffsetB = 16;
                    }
               }
               else
               {
                    printOffsetB = 24;
               }
               if (wholeNumber >= 0)
               {
                    printOffsetB = printOffsetB + 8;
               }
               if ((loop == 2) && (modMode[3] == 2))
               {
                    printOffsetB = printOffsetB + 8;
               }
               printOffsetA = 48;

               if ((modMode[3] == 1) | (loop == 3))
               {
                    if (decimalNumber < 100)
                    {
                         printStringNumber(MenuPosition[0]+printOffsetA-4,MenuPosition[1],"",0);
                         printOffsetC = 8;
                    }
                    else
                    {
                         printOffsetC = 0;
                    }
               }

               printStringNumber(MenuPosition[0]+printOffsetB,MenuPosition[1],"",wholeNumber);
               if ((modMode[3] == 1) | (loop == 3))
               {
                    printString(MenuPosition[0]+printOffsetA,MenuPosition[1],".");
                    printStringNumber(MenuPosition[0]+printOffsetA-4+printOffsetC,MenuPosition[1],"",decimalNumber);
               }
               MenuPosition[1] = MenuPosition[1] + 10;
               //
               //
          }


     }

}

void printAnticheat()
{
     loadPosition();

     if (modMode[0] == 0x01)
     {
          GraphPtr = drawBox(GraphPtr, MenuPosition[0] + 18, MenuPosition[1] + 18, MenuPosition[0] + (12 * 8) + 19, MenuPosition[1] + 28, 0, 0,0, 175);
          loadFont();

          printString(MenuPosition[0],MenuPosition[1], "Practice  ON");

     }
     else if (modMode[4] > 0)
     {
          GraphPtr = drawBox(GraphPtr, MenuPosition[0] + 18, MenuPosition[1] + 18, MenuPosition[0] + (11 * 8) + 19, MenuPosition[1] + 28, 0, 0,0, 175);
          loadFont();

          printString(MenuPosition[0],MenuPosition[1], "Force Items");
     }
     else if (gameMode[3] > 0x00)
     {

          switch (gameMode[3])
          {
               // PRACTICE BUILD overlay text.
               case 0x01 :
               {
                    GraphPtr = drawBox(GraphPtr, MenuPosition[0] + 18, MenuPosition[1] + 18, MenuPosition[0] + (10 * 8) + 19, MenuPosition[1] + 28, 0, 0,0, 175);
                    loadFont();
                    printString(MenuPosition[0],MenuPosition[1], "Versus CPU");
                    break;
               }
               case 0x02 :
               {
                    GraphPtr = drawBox(GraphPtr, MenuPosition[0] + 18, MenuPosition[1] + 18, MenuPosition[0] + (9 * 8) + 19, MenuPosition[1] + 28, 0, 0,0, 175);
                    loadFont();
                    printString(MenuPosition[0],MenuPosition[1], "Debug CPU");
                    break;
               }
          }
     }
     else if (gameMode[4] > 0x00)
     {
          GraphPtr = drawBox(GraphPtr, MenuPosition[0] + 18, MenuPosition[1] + 18, MenuPosition[0] + (11 * 8) + 19, MenuPosition[1] + 28, 0, 0,0, 175);
          loadFont();

          printString(MenuPosition[0],MenuPosition[1], "Force Stats");
     }



}


void swapParameter(int directionIndex)
{
     //if directionIndex == 0, swap down;
     //if directionIndex == 1, swap up;
     if (directionIndex == 0)
     {
          switch(GlobalIntA)  //CurrentPage
          {
               case 0:
               {
                    if (gameMode[GlobalIntB-1 + GlobalCharC] > 0) //currentParameter  //menuOverflowIndex
                    {
                         gameMode[GlobalIntB-1 + GlobalCharC]--;
                    }
                    break;
               }
               case 1:
               {
                    if (modMode[GlobalIntB-1 + GlobalCharC] > 0) //currentParameter  //menuOverflowIndex
                    {
                         modMode[GlobalIntB-1 + GlobalCharC]--;
                    }
                    break;
               }
               case 2:
               {
                    if (renderMode[GlobalIntB-1 + GlobalCharC] > 0) //currentParameter  //menuOverflowIndex
                    {
                         renderMode[GlobalIntB-1 + GlobalCharC]--;
                    }
                    break;
               }
               case 3:
               {
                    if (GlobalIntB == 1) //currentParameter
                    {
                         if (GlobalIntC > 0)  //cupSelect
                         {
                              GlobalIntC--;
                         }
                    }
                    if (GlobalIntB > 1) //currentParameter
                    {
                         if (SYSTEM_Region == 0x00)
                         {
                              GlobalAddressA = (cup_PAL + (GlobalIntC * 8) + ((GlobalIntB - 2) * 2));
                         }
                         else
                         {
                              GlobalAddressA = (cup_NTSC + (GlobalIntC * 8) + ((GlobalIntB - 2) * 2));
                         }
                         short *l_courseID = (short *)GlobalAddressA;
                         if (*l_courseID > 0)
                         {
                              *l_courseID = *l_courseID - 1;
                              copyCourseTable(1);
                         }
                    }
                    break;
               }
               default:
               {
                    break;
               }


          }


     }
     else
     {
          switch(GlobalIntA)  //CurrentPage
          {
               case 0:
               {
                    if (gameMode[GlobalIntB-1 + GlobalCharC] < gameLimits[GlobalIntB-1 + GlobalCharC]) //currentParameter  //menuOverflowIndex
                    {
                         gameMode[GlobalIntB-1 + GlobalCharC]++;
                    }
                    break;
               }
               case 1:
               {
                    if (modMode[GlobalIntB-1 + GlobalCharC] < modLimits[GlobalIntB-1 + GlobalCharC]) //currentParameter  //menuOverflowIndex
                    {
                         modMode[GlobalIntB-1 + GlobalCharC]++;
                    }
                    break;
               }
               case 2:
               {
                    if (renderMode[GlobalIntB-1 + GlobalCharC] < renderLimits[GlobalIntB-1 + GlobalCharC]) //currentParameter  //menuOverflowIndex
                    {
                         renderMode[GlobalIntB-1 + GlobalCharC]++;
                    }
                    break;
               }
               case 3:
               {
                    if (GlobalIntB == 1) //currentParameter
                    {
                         if (GlobalIntC < 3)  //cupSelect
                         {
                              GlobalIntC++;
                         }
                    }
                    if (GlobalIntB > 1) //currentParameter
                    {
                         if (SYSTEM_Region == 0x00)
                         {
                              GlobalAddressA = (cup_PAL + (GlobalIntC * 8) + ((GlobalIntB - 2) * 2));
                         }
                         else
                         {
                              GlobalAddressA = (cup_NTSC + (GlobalIntC * 8) + ((GlobalIntB - 2) * 2));
                         }

                         short *l_courseID = (short *)GlobalAddressA;

                         if (*l_courseID < 19)
                         {
                              *l_courseID = *l_courseID + 1;
                              copyCourseTable(1);
                         }
                    }
                    break;
               }
               default:
               {
                    break;
               }
          }
     }




}



void printMenu()
{
     GraphPtr = drawBox(GraphPtr, 50, 10, 270, 127, 0, 0,0, 175);
     GraphPtr = drawBox(GraphPtr, 48, 8, 50, 127, 0, 0,0, 255);
     GraphPtr = drawBox(GraphPtr, 270, 8, 272, 127, 0, 0,0, 255);
     GraphPtr = drawBox(GraphPtr, 50, 8, 270, 10, 0, 0,0, 255);
     GraphPtr = drawBox(GraphPtr, 50, 125, 270, 127, 0, 0,0, 255);

     GraphPtr = drawBox(GraphPtr, 60, 32, 260, 33, 0, 0,0, 255);




     if (GlobalIntA == 3)   //CurrentPage
     {
          if (GlobalIntB == 0) //currentParameter
          {
               MenuPosition[0] = 157 - ((menuChar[GlobalIntA]) * 4);
               GraphPtr = drawBox(GraphPtr, MenuPosition[0], 17, MenuPosition[0] + (menuChar[GlobalIntA] * 8), 27, 200, 0, 0, 200);
          }
          else if (GlobalIntB == 1) //currentParameter
          {
               MenuPosition[0] = 155 - ((cupChar[GlobalIntC]) * 4);
               GraphPtr = drawBox(GraphPtr, MenuPosition[0], 40, MenuPosition[0] + (cupChar[GlobalIntC] * 8), 50, 200, 0, 0, 200);
          }
          else
          {
               if (SYSTEM_Region == 0x00)
               {
                    GlobalAddressA = (cup_PAL + (GlobalIntC * 8) + ((GlobalIntB - 2) * 2));
               }
               else
               {
                    GlobalAddressA = (cup_NTSC + (GlobalIntC * 8) + ((GlobalIntB - 2) * 2));
               }
               short *l_courseID = (short *)GlobalAddressA;
               MenuPosition[0] = 157 - ((courseChar[(long)*l_courseID]) * 4);
               MenuPosition[1] = ((GlobalIntB - 1) * 14) + 43;
               GraphPtr = drawBox(GraphPtr, MenuPosition[0], MenuPosition[1], MenuPosition[0] + (courseChar[(long)*l_courseID] * 8), MenuPosition[1]+11, 200, 0, 0, 200);
          }
     }
     else
     {
          if (GlobalIntB == 0) //currentParameter
          {
               MenuPosition[0] = 157 - ((menuChar[GlobalIntA]) * 4);
               GraphPtr = drawBox(GraphPtr, MenuPosition[0], 19, MenuPosition[0] + (menuChar[GlobalIntA] * 8), 29, 200, 0, 0, 200);
          }
          else
          {
               MenuPosition[1] = GlobalIntB * 18 + 33;
               GraphPtr = drawBox(GraphPtr, 55, MenuPosition[1], 60, MenuPosition[1]+5, 200, 0, 0, 200);
          }


          if (pageLimit[GlobalIntA] > 4)    //CurrentPage
          {
               if (GlobalCharC == 0)  //menuOverflowIndex
               {
                    if (GlobalCharB < 15)  //used for blinking menu +
                    {
                         GraphPtr = drawBox(GraphPtr, 157, 113, 165, 121, 0, 0, 0, 240);
                         GraphPtr = drawBox(GraphPtr, 158, 114, 164, 120, 200, 0, 0, 240);
                    }

               }
               else
               {
                    if (GlobalCharB < 15)  //used for blinking menu +
                    {
                         GraphPtr = drawBox(GraphPtr, 157, 37, 165, 45, 0, 0, 0, 240);
                         GraphPtr = drawBox(GraphPtr, 158, 38, 164, 44, 200, 0, 0, 240);
                    }
               }
          }
     }


     loadFont();


     if (SYSTEM_Region == 0x00)
     {
          printString(18,195,"PAL");
     }
     else
     {
          printString(18,195,"NTSC");
     }

     printString(0,205,"BUILD 4.0");
     printString(200,195,"OverKart");
     printString(216,205,"Team");

     LoopValue = 0;
     MenuPosition[0] = 138 - (menuChar[GlobalIntA] * 4);
     printString(MenuPosition[0],0,menuNames[GlobalIntA]);
     MenuPosition[1] = 30;

     switch(GlobalIntA)    //CurrentPage
     {
          case 0:
          {
               do{
                    printString(45,MenuPosition[1],gameOptions[LoopValue + (long)GlobalCharC]);
                    MenuPosition[0] = 200 - (gameChar[LoopValue+ (long)GlobalCharC][(long)gameMode[LoopValue + (long)GlobalCharC]] * 4);
                    printString(MenuPosition[0],MenuPosition[1],gameParameters[LoopValue+ (long)GlobalCharC][(long)gameMode[LoopValue + (long)GlobalCharC]]);
                    MenuPosition[1] = MenuPosition[1] + 18;
                    LoopValue++;
               } while (LoopValue < 4);
               break;
          }
          case 1:
          {
               do{
                    printString(45,MenuPosition[1],modOptions[LoopValue + (long)GlobalCharC]);
                    MenuPosition[0] = 200 - (modChar[LoopValue + (long)GlobalCharC][(long)modMode[LoopValue + (long)GlobalCharC]] * 4);
                    printString(MenuPosition[0],MenuPosition[1],modParameters[LoopValue + (long)GlobalCharC][(long)modMode[LoopValue + (long)GlobalCharC]]);
                    MenuPosition[1] = MenuPosition[1] + 18;
                    LoopValue++;
               } while (LoopValue < 4);
               break;
          }
          case 2:
          {
               do{
                    printString(45,MenuPosition[1],renderOptions[LoopValue + (long)GlobalCharC]);
                    MenuPosition[0] = 200 - (renderChar[LoopValue + (long)GlobalCharC][(long)renderMode[LoopValue + (long)GlobalCharC]] * 4);
                    printString(MenuPosition[0],MenuPosition[1],renderParameters[LoopValue + (long)GlobalCharC][(long)renderMode[LoopValue + (long)GlobalCharC]]);
                    MenuPosition[1] = MenuPosition[1] + 18;
                    LoopValue++;
               } while (LoopValue < 4);
               break;
          }
          case 3:
          {
               MenuPosition[0] = 135 - (cupChar[GlobalIntC] * 4);
               printString(MenuPosition[0],22,cupNames[GlobalIntC]);
               MenuPosition[1] = 40;
               do{
                    if (SYSTEM_Region == 0x00)
                    {
                         GlobalAddressA = (cup_PAL + (GlobalIntC * 8) + LoopValue * 2);
                    }
                    else
                    {
                         GlobalAddressA = (cup_NTSC + (GlobalIntC * 8) + LoopValue * 2);
                    }
                    short *l_courseID = (short *)GlobalAddressA;
                    MenuPosition[0] = 138 - (courseChar[(long)*l_courseID] * 4);
                    printString(MenuPosition[0],MenuPosition[1],courseNames[(long)*l_courseID]);
                    MenuPosition[1] = MenuPosition[1] + 14;
                    LoopValue++;
               } while (LoopValue < 4);
               break;
          }
          default:
          {
               break;
          }
     }
     if (GlobalIntA != 3)    //CurrentPage
     {
          if (pageLimit[GlobalIntA] > 4)
          {
               if (GlobalCharC == 0)  //menuOverflowIndex
               {
                    if (GlobalCharB < 15)  //used for blinking menu +
                    {
                         printString(137,93,"+");
                    }

               }
               else
               {
                    if (GlobalCharB < 15)  //used for blinking menu +
                    {
                         printString(137,17,"+");
                    }
               }
          }
     }



     g_mlogoY = 0x00000075;
     g_mflagID = 0;
     g_mpressstartID = 0;
     g_mracewayTime = 0;


}



void titleMenu(void)
{
     if (!GlobalBoolC)
     {
          loadCoin();
          GlobalBoolC = true;
     }
     if (GlobalCharB > 30)  //used for blinking menu +
     {
          GlobalCharB = 0;
     }
     else
     {
          GlobalCharB++;  //used for blinking menu +
     }


     if(titleDemo > 4)
     {
          titleDemo = 4;   //This is a timer that runs at the title screen. Locking at 4 Prevents the demo courses from being displayed.
     }
     

     // Reset the MenuButtonHeld timer. This is set to 0x01 when a button is held down.
     // Used for advancing menu when direction is held.
     *targetAddress = (long)(&GenericInput);
     *sourceAddress = (long)(&MenuButtonHeld);
     *tempPointer = (long)(&ButtonTimer);

     if (c_Input > 0x00)
     {
          GenericInput = c_Input;
     }
     else
     {
          GenericInput = d_Input;
     }

     if (GenericInput == 0)
     {
          
          MenuButtonHeld = 0;
          ButtonTimer = 0;  //Button Held Timer
     }
     else
     {
          ButtonTimer = ButtonTimer + 1;  //Button Held Timer          
          if (ButtonTimer >= 9)
          {    
               MenuButtonHeld = 0;
               ButtonTimer = 0;  //Button Held Timer               
          }
     
          if ((titleDemo > 3) && (menuScreenB <= 0x03))
          {

               
               //MenuButtonHeld is set to 0x01 when a button is held down.
               if(MenuButtonHeld < 1)
               {
                    
                    // Uses the Control Stick or Dpad to switch through the menu.
                    switch(GenericInput)
                    {
                         //Increase the current menu Parameter by 1
                         case 0x01 :
                         {
                              MenuButtonHeld = 1;
                              if (GlobalIntB > 0) //currentParameter
                              {
                                   swapParameter(1);
                              }
                              else
                              {
                                   if (GlobalIntA < 3)
                                   {
                                        GlobalIntA++;
                                        GlobalCharC = 0;
                                        playSound(0x4900801A);
                                   }
                              }
                              break;

                         }
                         //Decrease the current menu Parameter by 1
                         case 0x02 :
                         {
                              MenuButtonHeld = 1;
                              if (GlobalIntB > 0) //currentParameter
                              {
                                   swapParameter(0);
                              }
                              else
                              {
                                   if (GlobalIntA > 0)
                                   {
                                        GlobalIntA--;
                                        GlobalCharC = 0;
                                        playSound(0x4900801A);
                                   }
                              }
                              break;

                         }
                         //Move forward to next option
                         case 0x04 :
                         {
                              MenuButtonHeld = 1;
                              if (GlobalIntB + GlobalCharC < pageLimit[GlobalIntA]) //currentParameter
                              {
                                   if ((GlobalIntB == 4) && (GlobalIntA < 3))
                                   {
                                        GlobalCharC++;
                                   }
                                   else
                                   {
                                        GlobalIntB++; //currentParameter
                                   }

                              }
                              break;

                              //
                         }
                         //Move backward to previous option
                         case 0x08 :
                         {
                              MenuButtonHeld = 1;
                              if (GlobalIntB + GlobalCharC > 0) //currentParameter
                              {
                                   if ((GlobalIntB == 1) && (GlobalIntA < 3) && (GlobalCharC > 0))
                                   {
                                        GlobalCharC--;
                                   }
                                   else
                                   {
                                        GlobalIntB--; //currentParameter
                                   }

                              }
                              break;
                         }


                    }
                    // End of menu Dpad code.


               }
          }
     }
     // Now print the menu using the menuFlag and parameterFlag options above.
     checkStats(gameMode[4]);  //check player stats
     printMenu();

     
     
     //
     //
     //
     // End of TITLE MENU code

     // This handles the FASTRESET hack in the Dpad Menu g_InGame




}
