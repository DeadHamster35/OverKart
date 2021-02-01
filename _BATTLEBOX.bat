cls
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "BattleBox\Core.c" -o "BattleBox\Core.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "BattleBox\MarioKartMenu.c" -o "BattleBox\MarioKartMenu.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "BattleBox\BattleBoxObject.c" -o "BattleBox\BattleBoxObject.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "library\MarioKart3D.c" -o "library\MarioKart3D.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "library\MarioKartObjects.c" -o "library\MarioKartObjects.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "library\SharedFunctions.c" -o "library\SharedFunctions.o" 
ARMIPS\bin\armips "BattleBox\MAKE.asm"
ARMIPS\bin\n64crc "BattleBox\ROM\mod.z64"
