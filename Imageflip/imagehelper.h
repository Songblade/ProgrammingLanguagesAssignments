#ifndef __IMAGEHELP_H__
#define __IMAGEHELP_H__

#include <stdio.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define MISSING_ARGUMENTS 0b1
#define INVALID_OPERATION 0b10
#define INPUT_FILE_ERROR  0b100
#define OUTPUT_FILE_ERROR 0b1000
#define INVALID_BMP_FILE  0b10000

// determine the proper offsets from the BMP specs
#define HEADER_SIZE 54
#define DATAOFFSET_OFFSET 10
#define WIDTH_OFFSET 18
#define HEIGHT_OFFSET 22
#define BITS_PER_PX_OFFSET 28

typedef struct {
    uint dataOffset; // Offset of the image data
    uint pxWidth;    // Width of the image in pixels
    uint pxHeight;   // Height of the image in pixels
    uint bitDepth;   // Number of bits used to represent a single pixel
    uint byteWidth;  // Width of a row in bytes
    uint fileSize; // the size of the file, added by me
} ImageInfo;

char extractOperation(char *opString);

FILE *openFileForReading(const char *filename); // not using, because doing this is one line anyway

FILE *openFileForWriting(const char *filename); // same here

int isBMPFile(char *fileName);

uint readBytesFromFile(FILE *fp, uint byteCount, char *buffer);

uint writeBytesToFile(FILE *fp, uint byteCount, char *buffer);

ImageInfo extractDataFromHeader(const char *header);

char declareOperation(char operation);

void moveDataBetweenFiles(FILE *input, FILE *output, uint start, uint end);

void flipHorizontal(char* bitMap, ImageInfo info);

void flipVertical(char* bitMap, ImageInfo info);

void swapBytes(char *left, char *right, uint count);

#endif
