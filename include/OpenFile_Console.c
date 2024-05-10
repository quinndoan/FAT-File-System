#include "OpenFile_Console.h"

int OpenFileHandler(int argc, char *argv[])
{
    if (argc == 1)
    {
        Open_File("./floppy.img");
    }
    else
    {
        if (strcmp(argv[1], "-h") == 0)
        {
            GUIDE();
            return 0;
        }
        Open_File(argv[1]);
    }
    return 1;
}
void GUIDE()
{
    printf("This is a FAT structure reader program\n");
    printf("Usage: read [target]\n");
    printf("%5s -h%11s%8s\n", " ",":", "display Guide");
    printf("%5s [target]%5s%8s\n", " ",":", "your file path, relatively to where you call run.exe, ideally in the same directory\n sample command would be: './read.exe ./floppy.img'");
}