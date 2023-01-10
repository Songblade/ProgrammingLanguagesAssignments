#include "imagehelper.h"

// implement imagehelper functions

char extractOperation(char *opString) {
    // this first part turns the String to lowercase
    char index = 0;
    char letter = opString[index];
    char lowerCaseString[strlen(opString) + 1];
    while (letter != '\0') {
        if (letter >= 65 && letter <= 90) {
            lowerCaseString[index] = opString[index] + 32;
        } else {
            lowerCaseString[index] = opString[index];
        }
        index++;
        letter = opString[index];
    }
    lowerCaseString[index] = '\0';

    if (!strcmp(lowerCaseString, "h")) { // not means equals 0
        return 'H';
    } else if (!strcmp(lowerCaseString, "v")) {
        return 'V';
    } else if (!strcmp(lowerCaseString, "hv")) {
        return 'B';
    } else {
        return 0; // means we have an error, I choose 0 because it is false
    }
}

int isBMPFile(char* fileName) {
    // this should get the substring to the final ., which should mean the file type
    // it then checks that the end is .bmp
    char* fileEnd = strrchr(fileName, '.');
    return !strcmp(".bmp", fileEnd);
    // if they are equal, strcmp returns 0, which means false, so I have to not it before returning it
}

uint readBytesFromFile(FILE *fp, uint byteCount, char *buffer) {
    // I can't use fgets, because that stops at a newline, which isn't applicable here
        // and could cause errors
    int i;
    for (i = 0; i < byteCount; i++) {
        char byte = (char) getc(fp);
        buffer[i] = byte;
        
    }

    return 1; // means operation was successful, file didn't end on us
}

uint writeBytesToFile(FILE *fp, uint byteCount, char *buffer) {
    for (uint i = 0; i < byteCount; i++) {
        putc(buffer[i], fp);
    }
    return 1;
}

/**
 * Note: This might not work
 * @param bytes an array of chars
 * @param numBytes length of bytes that we care about
 * @return the first 4 bytes of the array combined converted to a uint
 */
uint convertBytesToUInt(const char* bytes, char numBytes) {
    uint returnValue = 0;
    for (char i = 0; i < numBytes; i++) {
     
        if (bytes[i] >= 0) {
            returnValue += (bytes[i] << (8 * i));
        } else {

            returnValue += ((256 + bytes[i]) << (8 * i));
        }
    
    }
    return returnValue;

}

/**
 * Extracts the header info and also prints it to the screen
 * @param header whose info we are extracting
 * @return the header info
 */
ImageInfo extractDataFromHeader(const char *header) {
    ImageInfo info;

    info.dataOffset = convertBytesToUInt(header + DATAOFFSET_OFFSET, 4);

    info.pxWidth = convertBytesToUInt(header + WIDTH_OFFSET, 4);

    info.pxHeight = convertBytesToUInt(header + HEIGHT_OFFSET, 4);
 
    info.bitDepth = convertBytesToUInt(header + BITS_PER_PX_OFFSET, 2);
    info.byteWidth = (uint) ((info.bitDepth * info.pxWidth + 31) / 32.0) * 4;
    info.fileSize = convertBytesToUInt(header + 2, 4);

    printf("px width: %d\npx height: %d\nbit depth: %d\nbyte width: %d\ndata offset: 0x%x\n",
           info.pxWidth, info.pxHeight, info.bitDepth, info.byteWidth, info.dataOffset);

    return info;
}

char declareOperation(char operation) {
    switch (operation) {
        case 'H':
            printf("Flipping the image horizontally\n");
            return 1;
        case 'V':
            printf("Flipping the image vertically\n");
            return 1;
        case 'B':
            printf("Flipping the image horizontally and vertically\n");
            return 1;
        default:
            printf("We have been asked to do an unknown operation? This should be impossible\n");
            return 0;
    }
}

void moveDataBetweenFiles(FILE *input, FILE *output, uint start, uint end) {
    for (uint i = start; i < end; i++) {
        fputc(fgetc(input), output);
        // should move data from the input to the output without changing or examining it
        // Letting me ignore whatever buffer is between the header and the offset
    }
}

void flipRow(char* row, ImageInfo info) {
    char* leftLoc = row;
    char* rightLoc = row + (info.pxWidth - 1) * info.bitDepth / 8;
    // we are setting the location of our pointers at either side of the row
    // right should be at the beginning of the pixel at the end of the row
    // I can't multiply by the byteWidth in case there is padding
    while (rightLoc > leftLoc) {
        // means will keep flipping so long as right is after left
        // If they are equal, we have reached the middle, and don't need to move it
        // If they are less, we have crossed over
        swapBytes(leftLoc, rightLoc, info.bitDepth / 8);
        leftLoc += info.bitDepth/8;
        rightLoc -= info.bitDepth/8;
    }
}

/**
 * Swaps the 2 pixels
 * @param left pixel
 * @param right pixel
 * @param count number of bytes in the pixels to be swapped
 */
void swapBytes(char *left, char *right, uint count) {
    char temp[count];
    for (int i = 0; i < count; i++) {
        temp[i] = left[i];
        left[i] = right[i];
        right[i] = temp[i];
    }
}

void flipHorizontal(char* bitMap, ImageInfo info) {
    for (uint row = 0; row < info.pxHeight; row++) {
        flipRow(bitMap + row * info.byteWidth, info);
        // we flip each row, where we are inputting the current location of the cursor
    }
}

void flipColumn(char* column, ImageInfo info) {
    char* bottomLoc = column;
    char* topLoc = column + (info.pxHeight - 1) * info.byteWidth;
    // we are setting the location of our pointers at either end of the column
    // top should be the pixel in the column of the bottom row
    while (topLoc > bottomLoc) {
        // means will keep flipping so long as bottom is after top
        // If they are equal, we have reached the middle, and don't need to move it
        // If they are less, we have crossed over
        swapBytes(topLoc, bottomLoc, info.bitDepth / 8);
        bottomLoc += info.byteWidth; // increasing or decreasing by byte width should
        topLoc -= info.byteWidth; // keep us in the same column, but on a different row
    }
}

void flipVertical(char* bitMap, ImageInfo info) {
    for (uint column = 0; column < info.pxWidth; column++) {
        flipColumn(bitMap + column * info.bitDepth / 8, info);
        // we flip each column, where we are inputting the current location of the cursor
        // since the columns aren't stored together, we point to the pixel in the column in the
            // current row
    }
}