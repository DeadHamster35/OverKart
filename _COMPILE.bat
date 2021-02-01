cls

ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "OverKart\CustomLevels.c" -o "OverKart\CustomLevels.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "OverKart\MarioKartAI.c" -o "OverKart\MarioKartAI.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "OverKart\MarioKartMenu.c" -o "OverKart\MarioKartMenu.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "OverKart\MarioKartPractice.c" -o "OverKart\MarioKartPractice.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "OverKart\OKCustomObjects.c" -o "OverKart\OKCustomObjects.o" 
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "OverKart\OverKart.c" -o "OverKart\OverKart.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "OverKart\OverKartVariables.c" -o "OverKart\OverKartVariables.o"

ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "library\LibraryVariables.c" -o "library\LibraryVariables.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "library\MarioKart3D.c" -o "library\MarioKart3D.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "library\MarioKartObjects.c" -o "library\MarioKartObjects.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "library\MarioKartStats.c" -o "library\MarioKartStats.o"
ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "library\SharedFunctions.c" -o "library\SharedFunctions.o" 

ARMIPS\bin\armips "OverKart\BUILD.asm"
ARMIPS\bin\n64crc "OverKart\ROM\BASE.z64"
