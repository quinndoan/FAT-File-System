#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char filename[9];
    char ext[4];
    unsigned char attr;
    unsigned short time;
    unsigned short date;
    unsigned short start_cluster;
    unsigned int size;
} DirEntry;

void print_entry(DirEntry *entry) {
    printf("Filename: %s\n", entry->filename);
    printf("Extension: %s\n", entry->ext);
    printf("Attributes: %02X\n", entry->attr);
    printf("Time: %04X\n", entry->time);
    printf("Date: %04X\n", entry->date);
    printf("Start cluster: %04X\n", entry->start_cluster);
    printf("Size: %u\n", entry->size);
}

void print_aligned_entry(DirEntry *entry) {
    printf("Filename: %-8s", entry->filename);
    printf("Extension: %-3s ", entry->ext);
    printf("Attributes: %02X  ", entry->attr);
    printf("Time: %04X  ", entry->time);
    printf("Date: %04X  ", entry->date);
    printf("Start cluster: %04X  ", entry->start_cluster);
    printf("Size: %u\n", entry->size);
}

void decode_root_dir(FILE *file, long offset) {
    fseek(file, offset, SEEK_SET);

    printf("---------------------------------------------------------------------\n");
    printf("Filename	  Extension	 Attributes	Time	    Date	Start cluster	     Size\n");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < 16; i++) {
        DirEntry entry;
        fread(entry.filename, 1, 8, file);
        entry.filename[8] = '\0'; 
        fread(entry.ext, 1, 3, file);
        entry.ext[3] = '\0'; 
        fread(&entry.attr, 1, 1, file);
        fseek(file, 10, SEEK_CUR); // Skip reserved bytes
        fread(&entry.time, 2, 1, file);
        fread(&entry.date, 2, 1, file);
        fread(&entry.start_cluster, 2, 1, file);
        fread(&entry.size, 4, 1, file);

        print_aligned_entry(&entry);
    }

    printf("---------------------------------------------------------------------\n");
}

int main() {
    FILE *file = fopen("C://Users//Nitro Tiger//Downloads//floppy.img", "rb");
    if (!file) {
        printf("Could not open file\n");
        return 1;
    }

    decode_root_dir(file, 0x2600);

    fclose(file);
    return 0;
}