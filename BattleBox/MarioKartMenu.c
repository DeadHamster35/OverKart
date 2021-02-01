#include <math.h>
#include "../library/GameVariables/NTSC/GameOffsets.h"
#include "../library/GameVariables/NTSC/OKHeader.h"
#include "MarioKartMenu.h"
#include "Core.h"

int menuX;
int menuY;



void titleMenu(void)
{
     menuX  = 0;
     menuY = 0;
}

void printGPTime(float printTime)
{

     int wholeNumber = 0;
     int decimalNumber = 0;
     int printOffsetA, printOffsetB = 0;


     wholeNumber = (int) printTime;
     decimalNumber = (int) ((printTime - wholeNumber) * 100);

     int minutes = 0;
     int seconds = 0;

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
     menuY = 180;
     menuX = 70;

     printString(menuX,menuY,"Total Time:");

     menuX = 160;


     printString(menuX + printOffsetA, menuY, "'");
     if (seconds < 10)
     {
          printStringNumber(menuX + printOffsetA,menuY,"",0);
          printOffsetA = printOffsetA + 8;
          printOffsetB = printOffsetB + 8;
     }

     printString(menuX + printOffsetB, menuY, "\"");
     if (decimalNumber < 10)
     {
          printStringNumber(menuX+printOffsetB,menuY,"",0);
          printOffsetB = printOffsetB + 8;
     }




     printStringNumber(menuX,menuY,"",minutes);
     printStringNumber(menuX + printOffsetA,menuY,"",seconds);
     printStringNumber(menuX+printOffsetB,menuY,"",decimalNumber);



}
