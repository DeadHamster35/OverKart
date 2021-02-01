//These are new custom RAM values
//0x80400000 - 0x804FFFFF is restricted for OverKart64 functions and data.
//0x80500000 - 0x805FFFFF is reserved for Custom Course Assembly and data.
//0X80600000 - 0X80780000 should be safe for any other custom code.
//The end of RAM is course data, from 0x80800000 backwards.
//This varies based on the size of data for the current course. Be cautious!


//804396C4 targetAddress;?

.definelabel ok_HeaderROM, 0xBE9178
.definelabel ok_SaveSize, 0x28980
.definelabel ok_HeaderSize, 0x1400
.definelabel ok_MenuSize, 0x2800
.definelabel ok_CourseHeaderSize, 0x6C


.definelabel ok_SaveState, org(EndRAMData)
.definelabel ok_HeaderOffsets, ok_SaveState + ok_SaveSize
.definelabel ok_MenuOffsets, ok_HeaderOffsets + ok_HeaderSize
.definelabel ok_CourseHeader, ok_MenuOffsets + ok_MenuSize
.definelabel ok_CourseTable, ok_CourseHeader + ok_CourseHeaderSize  //0x28 bytes

.definelabel ok_ItemTable, ok_CourseTable + 0x28

.definelabel ok_Target, ok_ItemTable + 0x20
.definelabel ok_Source, ok_Target + 0x4
.definelabel ok_Pointer, ok_Source + 0x4
.definelabel ok_FreePointer, ok_Pointer + 0x4  //set value after loading data.
.definelabel ok_RedCoinList, ok_FreePointer + 0x4
.definelabel ok_Credits, ok_RedCoinList + 0x50 //8 bytes per coin * 10 for space
.definelabel ok_MapTextureData, ok_Credits + 0x40 // up to 0x3000 bytes
.definelabel ok_scrolltranslucent, ok_MapTextureData + 0x3000  //hold a ton of potential scrolling objects or translucent objects. 

.definelabel ok_redcoinsprite, ok_scrolltranslucent + 0x4000
.definelabel ok_Logo, ok_redcoinsprite +  0x200;  //logo for intro, can be overwritten after.
.definelabel ok_ModelData, ok_Logo; // overwrites logo after. 

.definelabel ok_FreeSpace, ok_ModelData + ok_ModelDataRawSize; //free RAM for temp storage.
.definelabel ok_ASMJump, ok_FreeSpace + 0x10000
.definelabel ok_Knowledge, 0x807F0000