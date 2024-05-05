# File system & Disklayout

# FAT File system
## Intro - overall
    based on `file map model`
    types:
        categorized by the construction of the actual file allocation table.
        - 12b: tend to be for floppy & small hard disk 
        - 16b: 
        - 32b: more complex
## Basic layout:
- For the sake of simplicity,
    - consider  a disk as a simple storage area made up just of a number of sectors numbered consecutively 
    - Sector will be considered as blocks (for now)
    - All blocks unified in size: 512 bytes
    - Multiple blocks can be grouped in pairs (fours, 8, etc) called allocation unit.
- FAT file system works in `allocation unit`
## FAT (File allocation table)
### Terminologies
- each entry in FAT is 2 bytes in len
- allocation units:
            numbered from the start of the disk
- cluster : disk data area divided into clusters <br>
         the same thing as allocation units, but numbered differently  <br>
            (numbered from the start of the disk data area) <br>
        `The clusters are numbered starting at 2, not 0! So the above calculation has to have 2 added to it to get the cluster number of a given allocation unit...and a cluster number is converted to an allocation unit number by subtracting 2...! ` <br>
        --> hence those 2 FAT entries are reserved n special -> Clusters 0 and 1 don't exist  <br>
        - other than that, Entry N relates to cluster N. 
    - cluster content: contains the successor cluster number
- successor cluster number: 
    - The  number of the cluster that follows this one in the file to which the current cluster belongs. 
    - The last cluster of a file has the value 0xffff in its FAT entry to indicate that there are no more clusters. 
- Sector <sector and cluster may be similar ?????>
- byte storages: LSB <least significant byte> stored first, then MSB <most significant byte>
    eg: 
     ```
     at position 3 has a value of 0x15, and the byte at position 4 has a value of 0x74, they together make up a word with value 0x7415 (not 0x1574). 
     ```
### Structure
| Area description   |  Area size |  
|---|---|
|Boot block   | 1 block  |  
|FAT (may be multiple copies)   |  Depends on file system size | 
| Disk root directory | Variable (selected when disk is formatted)  |  
| File data area  |  The rest of the disk  |  
	
### Properties
- the number of FATs is stored at offset 0x10
- size of a FAT; this is at offsets 0x16 and 0x17
-  `number of blocks that appear before the root` =   (size of FAT)*(number of FATs) + 1
- FAT type: 0x36 (from 0x00)
- Number of root directory entries : 0x11 (from 0x00)	Number of root directory entries (including unused ones).
    -> to dec: number of entries
- root, each file data holds: 32bytes

| Offset  |Length   | Description  | 
|---|---|---|
|0x00    | 8 bytes   | Filename  |   
|0x08 | 3 bytes | Filename extension  |  
|0x0b   | 1 byte   |File attributes   | 
|0x0c   | 10 bytes   | Reserved  | 
|0x16   |2 bytes   | Time created or last updated  | 
|0x18   | 2 bytes   | Date created or last updated  | 
|0x1a   | 2 bytes   | Starting cluster number for file  | 
|0x1c  | 4 bytes  | File size in bytes   | 



 	

# References:
http://www.tavi.co.uk/phobos/fat.html#file_allocation_table
https://fromthegroundupmyway.blogspot.com/2020/10/it-is-time-to-look-into-fat.html
https://www.eit.lth.se/fileadmin/eit/courses/eitn50/Literature/fat12_description.pdf

# TOOLS:
https://hexed.it/https://hexed.it/
