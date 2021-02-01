.n64
.open "OverKart\ROM\stock.z64", "OverKart\ROM\BASE.z64", 0



.definelabel PAYLOAD_ROM, 		0x00C00000
.definelabel PAYLOAD_RAM, 		0x80400000
.definelabel DMA_FUNC,    		0x80001158
.definelabel RAM_END,           org(EndRAMData)
.definelabel DMA_MAX_LENGTH,       org(EndRAMData) - org(StartRAMData)
.definelabel Printf, 			0x800D6420
.definelabel ok_ModelDataRawSize,     filesize("RawAssets\ModelData\ModelData.raw")

.definelabel itemChanceHi,    hi(org(ok_ItemTable))
.definelabel itemChanceLo,    lo(org(ok_ItemTable))

.include "library\GameVariables\NTSC\GameOffsets.asm"
.include "library\GameVariables\NTSC\StatsOffsets.asm"
.include "library\OKHeader.asm"
.include "library\GameVariables\NTSC\OKAssembly.asm"
.include "RawAssets\ModelData\ModelData.asm"


.org 0x113FBA
.halfword 0x8080
.org 0x113FCE
.byte 0x00






.org 0x10C7E2
.halfword hi(DisplayHopTable)
.org 0x10C7EA
.halfword lo(DisplayHopTable)
.org 0x10C7D4
.word 0
.org 0x10C7D8
.word 0


.org 0x10CB44
J FreeDraw



.org 0x109AAA
.halfword hi(CollisionHopTable)
.org 0x109AB2
.halfword lo(CollisionHopTable)
.org 0x109A90
.word 0
.org 0x109A9C
.word 0



//original hook placement
.org 0x34BC //RAM address 0x800028BC
J GlobalCustomCode
NOP






//title screen hook
.org 0x957D0 //RAM address 0x80094BD0
J CustomCodeTitleScreen
NOP




//1p
.org 0x2214
J race1P
NOP

//2p
.org 0x269C
J race2P
NOP

//mp
.org 0x28F8
J raceMP
NOP


.org 0x17EC //RAM address 0x80000BEC
LUI a0, 0x8040 //RAM address
LUI a1, hi(PAYLOAD_ROM)
ADDIU a1, a1, lo(PAYLOAD_ROM) //DMA from ROM address 0x00C00000
LUI a2, hi(DMA_MAX_LENGTH)
JAL DMA_FUNC
ADDIU a2, lo(DMA_MAX_LENGTH)
J OriginalBootFunction
NOP








.headersize 0x7F800000
.org PAYLOAD_RAM



StartRAMData:

.align 0x10
bannerN:
.import "OverKart\\data\\banner_n.mio0.bin"        ;;  324

.align 0x10
bannerU:
.import "OverKart\\data\\banner_U.mio0.bin"        ;;  311

.align 0x10
set0:
.import "OverKart\\data\\Stock.png.MIO0"            ;;  87c
.align 0x10
set0end:

.align 0x10
set1:
.import "OverKart\\data\\Set1.png.MIO0"            ;;  7f5
.align 0x10
set1end:

.align 0x10
set2:
.import "OverKart\\data\\Set2.png.MIO0"            ;;  7fc
.align 0x10
set2end:

.align 0x10
set3:
.import "OverKart\\data\\Set3.png.MIO0"            ;;  808
.align 0x10
set3end:

.align 0x10
set4:
.import "OverKart\\data\\Set4.png.MIO0"            ;;  800
.align 0x10
set4end:


.align 0x10
OriginalBootFunction: //we overwrite this when DMAing our code
//therefore, make sure it gets ran or the game wont boot
LUI    T6, 0x8030
LUI    AT, 0x1FFF
ORI    AT, AT, 0xFFFF
ADDIU t6, t6, 0x9F80
AND t7, t6, at
LUI at, 0x8015
J 0x800012AC //jump back to where execution should be on boot
SW t7, 0x02B4 (at)

.align 0x10
CustomCodeTitleScreen:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp)
JAL	0x80095574 //run what we overwrote with our hook
NOP
JAL titleMenu
NOP
LW ra, 0x001C (sp)
ADDIU sp, sp, 0x20
J 0x80094BD8 //jump back to where we were
NOP
NOP


.align 0x10
GlobalCustomCode:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp) //push ra to the stack
NOP
JAL allRun
NOP
LW ra, 0x001C (sp) //pop ra from the stack
ADDIU sp, sp, 0x20
J 0x8000286C //tells the game where to jump back to, dont remove
NOP


.align 0x10
race1P:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp) //push ra to the stack
NOP
JAL gameCode
NOP
LW ra, 0x001C (sp) //pop ra from the stack
ADDIU sp, sp, 0x20
LUI a0, 0x800E
LHU a0, 0xC520 (a0)
LUI a1, 0x800E
J 0x8000161C
NOP

.align 0x10
race2P:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp) //push ra to the stack
NOP
JAL gameCode
NOP
LW ra, 0x001C (sp) //pop ra from the stack
ADDIU sp, sp, 0x20
LUI t3, 0x800E
LW t3, 0xC5E8 (t3)
J 0x80001AA4
NOP



.align 0x10
raceMP:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp) //push ra to the stack
NOP
JAL gameCode
NOP
LW ra, 0x001C (sp) //pop ra from the stack
ADDIU sp, sp, 0x20
LUI v0, 0x800E
LW v0, 0xC5E8 (v0)
J 0x80001D00
NOP




.align 0x10
.importobj "library\LibraryVariables.o"
.align 0x10
.importobj "OverKart\OverKartVariables.o"
.align 0x10
.importobj "library\MarioKart3D.o"
.align 0x10
.importobj "library\MarioKartObjects.o"
.align 0x10
.importobj "library\MarioKartStats.o"
.align 0x10
.importobj "library\SharedFunctions.o"
.align 0x10
.importobj "OverKart\CustomLevels.o"
.align 0x10
.importobj "OverKart\MarioKartAI.o"
.align 0x10
.importobj "OverKart\MarioKartMenu.o"
.align 0x10
.importobj "OverKart\MarioKartPractice.o"
.align 0x10
.importobj "OverKart\OKCustomObjects.o"
.align 0x10
.importobj "OverKart\OverKart.o"


.align 0x10
DisplayHop:
MOVE  $a0, $s1
JAL   DisplayObject
MOVE  $a1, $s0
J     0x802A34D4
NOP


.align 0x10
FreeDraw:
JAL Draw3DRacer
NOP
LW ra, 0x24 (sp)
LW s0, 0x18 (sp)
LW s1, 0x1C (sp)
LW s2, 0x20 (sp)
JR ra
ADDIU sp, sp, 0x98

.align 0x10
CollisionHop:
LW    $t4, 0xbc($a3)
MOVE  $a0, $a3
LW    $ra, 0x1c($sp)
JAL  CollideObject
MOVE  $a1, $s0
J     0x802A0D44
LW    $ra, 0x1c($sp)


.align 0x10
DisplayHopTable:
.word 0x802A31E4, 0x802A31FC, 0x802A3214, 0x802A32EC
.word 0x802A3318, 0x802A3330, 0x802A3348, 0x802A34C0
.word 0x802A3378, 0x802A34D4, 0x802A34D4, 0x802A34D4
.word 0x802A34D4, 0x802A3390, 0x802A33A4, 0x802A33B8
.word 0x802A33CC, 0x802A322C, 0x802A33E4, 0x802A34D4  //19
.word 0x802A34D4, 0x802A33FC, 0x802A34D4, 0x802A3428  //23
.word 0x802A3244, 0x802A34D4, 0x802A325C, 0x802A328C  //27
.word 0x802A32A4, 0x802A32BC, 0x802A32D4, 0x802A3274  //31
.word 0x802A34D4, 0x802A3414, 0x802A34D4, 0x802A345C  //35
.word 0x802A3440, 0x802A34AC, 0x802A3470, 0x802A3484  //39
.word 0x802A3360, 0x802A34D4, 0x802A3498, 0x802A3300  //43
.word 0x802A33E4, DisplayHop, 0x802A33E4, 0x802A33E4  //47
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4  //51
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4  //55
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4  //59
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4  //63
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4  //67
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4  //71
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4  //75
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4  //79
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4
.word 0x802A33E4, 0x802A33E4, 0x802A33E4, 0x802A33E4 //99


.align 0x10
CollisionHopTable:
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09D4
.word 0x802A04E0, 0x802A063C, 0x802A0858, 0x802A04AC  //7
.word 0x802A0968, 0x802A0D40, 0x802A0CBC, 0x802A0AA4
.word 0x802A0D40, 0x802A0D40, 0x802A0D40, 0x802A0D40
.word 0x802A0D40, 0x802A09B0, 0x802A0D40, 0x802A0D40 //19
.word 0x802A0D40, 0x802A098C, 0x802A0D40, 0x802A09B0
.word 0x802A09B0, 0x802A0D40, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A0D40, 0x802A0D40, 0x802A0D40, 0x802A0D40
.word 0x802A0D40, 0x802A0D40, 0x802A0D40, 0x802A0D40 //39
.word 0x802A0744, 0x802A0C34, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, CollisionHop, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0 //59
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0 //79
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0
.word 0x802A09B0, 0x802A09B0, 0x802A09B0, 0x802A09B0 //99
.align 0x10

EndRAMData:




.headersize 0
.align 0x10
previewN:
.import "OverKart\\textures\\preview_n.mio0.bin"       ;;  c10
.align 0x10
previewU:
.import "OverKart\\textures\\preview_U.mio0.bin"       ;;  c64
.align 0x10
LogoROM:
.import "OverKart\\data\\logo.bin" ;; 0x3888
.align 0x10
ModelDataStart:
.import "RawAssets\\ModelData\\ModelData.bin"
.align 0x10
ModelDataEnd:



RCSpriteROM:
.import "OverKart\\data\\RedCoinSprite16.png.MIO0" ;; 0x4F0



.org 0xD00000
.word 0
.close
