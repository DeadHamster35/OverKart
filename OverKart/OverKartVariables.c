#include <stdbool.h>

//Main

short hsLabel, raceStatus, startupSwitch, courseSwapped = -1;
bool scrollLock = false;
int currentHeaderAddress = 0;




short gpCourseIndex, HotSwapID, hsGP, gpTimeCheck, courseValue = -1;
float gpTotalTime = 0;


int VersionNumber;
short MenuButtonHeld, ButtonHeld, ButtonTimer;
bool CustomASM;
//
//


//CustomLevels
int ScrollValues[32][2];
//
//



//Menu
short MenuPosition[2];
int wholeNumber = 0;
int decimalNumber = 0;
int printOffsetA, printOffsetB, printOffsetC, printOffsetD = 0;
int minutes = 0;
int seconds = 0;

char gameMode[5] = {0,0,0,0,0};
char modMode[5] = {0,0,0,0,0};
char renderMode[6] = {0,0,0,0,0,0};

char *menuNames[] = {"Game Options", "Mod Options","Render Options","Cup Editor"};
int menuChar[] = {12,11,14,10};
char *cupNames[] = {"Mushroom Cup","Flower Cup","Star Cup","Special Cup"};
int cupChar[] = {12,10,8,11};
char *courseNames[] = {"Mario Raceway", "Choco Mountain", "Bowser Castle", "Banshee Boardwalk","Yoshi Valley", "Frappe Snowland", "Koopa Troopa Beach", "Royal Raceway",
"Luigi Raceway", "Moo Moo Farm", "Toad Turnpike","Kalimari Desert","Sherbet Land","Rainbow Road","Wario Stadium", "Block Fort", "Skyscraper", "Double Deck", "DK Jungle Parkway","Big Donut"};
int courseChar[] = {13,14,13,17,12,15,18,13,13,12,13,15,11,12,13,10,10,11,17,9};


char *gameOptions[] = {"Red Coin Mode", "Mirror Mode", "All Cup", "AI State", "Racer Stats"};
char *gameParameters[][9] = {{"Off", "On"}, {"Off" , "On"}, {"Off" , "On"}, {"Regular","Force VS", "Debug"}, {"Default","Mario","Luigi","Yoshi","Toad","D.K.","Wario","Peach","Bowser"}};
int gameLimits[] = {1,1,1,2,8};
int gameChar[][9] = {{3,2}, {3,2}, {3,2},{7,8,5},{7,5,5,5,4,4,5,5,6}};

char *modOptions[] = {"Practice Mode", "Flycam", "Input Display", "Details", "Force Items"};
char *modParameters[][14] = {{"Off" , "On", "Map", "Dev"}, {"Off" , "On"}, {"Off" , "On"}, {"Off","On","Shortcut"},
{"Default","8th","7th","6th","5th","4th","3rd","2nd","1st","Banana","3 G. Shell", "3 R. Shell", "Star", "3 Shroom"}
};
int modLimits[] = {3,1,1,2,8};
int modChar[][14] = {{3,2,3,3}, {3,2},{3,2},{3,2,8},{7,3,3,3,3,3,3,3,3,6,10,10,4,8}};

char *renderOptions[] = {"Widescreen", "Anti-Alias", "3D Racer", "Screen Split", "Draw Dist.", "Game Tempo"};
char *renderParameters[][2] = { {"Off" , "On"}, {"Off" , "On"}, {"Off" , "On"},  {"Default", "2P Vertical"}, {"Default","Extended"}, {"Console","Emulator"}};
int renderLimits[] = {1,1,1,1,1,1};
int renderChar[][2] = { {3,2}, {3,2}, {3,2},{7,8}, {7,8}, {7,8}};

int pageLimit[] = {5,5,6,5};  // GAME - MOD - RENDER - CUP EDITOR


float AnalogInput[2];

int ItemChance[8];
//
//





//PracticeHack

int FlyCamPosition[3];

float FlyCamAngle, FlyCamRadian;
int FlyCamLook[2][2];
int LocalInput[2];
int InputColor[4];
char GenericInput, MapMode = 0;
short FlyCamSpeed = 5;




//InputDisplay Variables
char *names[] = {
	"A", "B", "Z", "S",
	"U", "D", "L", "R", // draw d-pad
	"", "", //unused bits
	"L", "R",
	"U", "D", "L", "R" //C buttons
};
char colors[][3] = {
	{  0, 192, 255}, //A: blue
	{  0, 255,   0}, //B: green
	{255, 255, 255}, //Z: white
	{255,   0,   0}, //Start: red
	{192, 192, 192}, {192, 192, 192}, //up, down
	{192, 192, 192}, {192, 192, 192}, //left, right
	{  0,   0,   0}, {  0,   0,   0}, //unused
	{255, 255, 255}, {255, 255, 255}, //L, R
	{255, 255,   0}, {255, 255,   0}, //C up, down
	{255, 255,   0}, {255, 255,   0}  //C left, right
};
char coords[][2] = {
	{3, 1}, //A
	{3, 2}, //B
	{5, 1}, //Z
	{3, 0}, //start
	{5, 0}, {5, 2}, {4, 1}, {6, 1}, //d-pad
	{0, 0}, {0, 0}, //unused
	{4, 0}, //L
	{6, 0}, //R
	{5, 0}, //C up
	{5, 2}, //C down
	{4, 1}, //C left
	{6, 1}  //C right
};
char *stickNames[] = {
	"U", "D", "L", "R","S"
};
char stickColor[][3] = {
	{192, 192, 192},
	{192, 192, 192},
	{192, 192, 192},
	{192, 192, 192},
	{255, 255, 255}
};
char stickCoord[][2] = {
	{1, 0}, //U
	{1, 2}, //D
	{0, 1}, //L
	{2, 1}, //R
	{1, 1} //stick
};





// Variables Draw3DRacer
short baseTurn, addTurn = 0;
//
//








//OKCustom Objects
short CoinPositions[8][3]; //8 Coins XYZ
//
//
char EndPoint;