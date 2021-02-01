// These are new custom RAM values
// 0x80400000 - 0x804FFFFF is restricted for OverKart64 functions and data.
// 0x80500000 - 0x805FFFFF is reserved for Custom Course Assembly and data.
// 0X80600000 - 0X80780000 should be safe for any other custom code.
// The end of RAM is course data, from 0x80800000 backwards.
// This varies based on the size of data for the current course. Be cautious!

extern long ok_SaveState;  //0x80420000
extern long ok_HeaderOffsets; //0x80450000
extern long ok_MenuOffsets; //0x80451400
extern long ok_CourseHeader; //0x80453C00

extern long ok_HeaderROM; //0xBE9178

extern long ok_Target; //0x80454D04
extern long ok_Source; //0x80454D08
extern long ok_Pointer; //0x80454D0C


extern long ok_ItemTable; //


extern long ok_CourseTable; //0x80454D50  //0x28 bytes

extern long ok_FreePointer;
extern long ok_RedCoinList;//0x80454D78
extern long ok_Credits;
extern long ok_MapTextureData; //0x80455000 //


extern long ok_Logo;
extern long ok_ModelData;
extern long ok_FreeSpace; 

extern long ok_RedCoinSprite;
extern long ok_ScrollTranslucent;

extern void ok_ASMJump(); //
extern long ok_Knowledge;







