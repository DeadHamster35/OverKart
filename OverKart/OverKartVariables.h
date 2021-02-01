
//Main

extern short hsLabel, raceStatus, startupSwitch, courseSwapped;
extern bool scrollLock;
extern int currentHeaderAddress;




extern short gpCourseIndex, HotSwapID, hsGP, gpTimeCheck, courseValue;
extern float gpTotalTime;


extern int VersionNumber;
extern char MenuButtonHeld, ButtonHeld, ButtonTimer;
extern bool CustomASM;
//
//


//CustomLevels
extern int ScrollValues[32][2];

//Menu
extern short MenuPosition[2];
extern int wholeNumber;
extern int decimalNumber;
extern int printOffsetA, printOffsetB, printOffsetC, printOffsetD;
extern int minutes;
extern int seconds;

extern char gameMode[5];
extern char modMode[5];
extern char renderMode[6];

extern char *menuNames[];
extern int menuChar[];
extern char *cupNames[];
extern int cupChar[];
extern char *courseNames[];
extern int courseChar[];

extern char *gameOptions[];
extern char *gameParameters[][9];
extern int gameLimits[];
extern int gameChar[][9];

extern char *modOptions[];
extern char *modParameters[][14];
extern int modLimits[];
extern int modChar[][14];

extern char *renderOptions[];
extern char *renderParameters[][2];
extern int renderLimits[];
extern int renderChar[][2];

extern int pageLimit[];

extern float AnalogInput[2];
//PracticeHack

extern int FlyCamPosition[];
extern float FlyCamAngle, FlyCamRadian;
extern int FlyCamLook[2][2];
extern int LocalInput[2];
extern int InputColor[4];
extern char GenericInput, MapMode;
extern short FlyCamSpeed;


//InputDisplay Variables
extern char *names[];
extern char colors[][3];
extern char coords[][2];
extern char *stickNames[];
extern char stickColor[][3];
extern char stickCoord[][2];


// Variables Draw3DRacer
extern short baseTurn, addTurn;


//OKCustom Objects

extern short CoinPositions[8][3]; //8 Coins XYZ
extern char EndPoint;