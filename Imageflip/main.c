#include <malloc.h>
#include "imagehelper.h"

/***************************************************
Expect two arguments in the following order:
Operation
Input file namepath

If less than two arguments were specified
Print: "Missing arguments"
Print: "Usage: imageflip <H|V|HV> <filename>"
Do not continue processing and return an error code of of MISSING_ARGUMENTS

If more than two arguments were specified:
Print: "Warning: Ignoring extra ? arguments"
(Continue processing)

If the operations were not one of {H, V, HV}:
Print: "Invalid operation: ?, must be one of {H, V, HV}"
Return an error code of INVALID_OPERATION
(Note, handle both upper- and lowercase letters)

If the input file could not be found/opened:
Print: "Could not open input file: filename"
Return an error code of INPUT_FILE_ERROR

 If the input file's header is incorrect
 (cannot read HEADER_SIZE bytes, or signature is not BM):
 Print: "File is not a valid BMP file"
 Return an error code of INVALID_BMP_FILE

Assume an output file name of "out.bmp"
If the output file could not be opened:
Print: "Could not open output file for writing: out.bmp"
Return an error code of OUTPUT_FILE_ERROR

If multiple errors exist (except in the case of MISSING_ARGUMENTS)
Your return code should incorporate all of the relevant codes
e.g., INVALID_OPERATION, INVALID_BMP_FILE
e.g., INVALID_OPERATION, INVALID_BMP_FILE, OUTPUT_FILE_ERROR
e.g., INPUT_FILE_ERROR, OUTPUT_FILE_ERROR
****************************************************/

int main(int argc, char *argv[]) {

    char operation; // what we are doing to the file, either H, V, or HV, but I will store HV as B to make things easier
    int errorCode = 0; // we will OR things to this when we have errors

    /*/ read and check program arguments
     * If less than two arguments were specified
        Print: "Missing arguments"
        Print: "Usage: imageflip <H|V|HV> <filename>"
        Do not continue processing and return an error code of MISSING_ARGUMENTS
    //*/
    if (argc < 3) { // 3, because the first arg is always the program file name
        printf("Missing arguments\n");
        printf("Usage: imageflip <H|V|HV> <filename>\n");
        errorCode |= MISSING_ARGUMENTS;
        return errorCode; // This is redundant, but I want to always return the same way
    }

    /*If more than two arguments were specified:
    Print: "Warning: Ignoring extra ? arguments"
    (Continue processing)*/
    if (argc > 3) {
        printf("Warning: Ignoring extra %d arguments\n", argc - 3);
    }

    /*If the operations were not one of {H, V, HV}:
    Print: "Invalid operation: ?, must be one of {H, V, HV}"
    Return an error code of INVALID_OPERATION
            (Note, handle both upper- and lowercase letters)*/
    // I am storing HV as B to use less memory and make things simpler
    operation = extractOperation(argv[1]);

    if (!operation) { // if the operation given wasn't a valid operation
        printf("Invalid operation: %s, must be one of {H, V, HV}\n", argv[1]);
        errorCode |= INVALID_OPERATION;
    }

    //Made sure prints operation correctly when not on IDE

    // open the input file for reading

    FILE *inputFile = fopen(argv[2], "rb");
    if (!inputFile) { // if there is something stopping us from reading the file
        printf("Could not open input file: %s\n", argv[2]);
        errorCode |= INPUT_FILE_ERROR;
    }

    // open the output file for writing

    FILE *outputFile = fopen("out.bmp", "wb");
    if (!outputFile) {
        errorCode |= OUTPUT_FILE_ERROR;
        printf("Could not open output file for writing: out.bmp\n");
    }

    if (errorCode & INPUT_FILE_ERROR) { // if we have an input file error, we won't be able to
        // start checking if it is a BMP file error, since we aren't supposed
        // to get both according to piazza, so I will return the error now
        if (outputFile) { // if we made the output file, close it. Otherwise, it might have errors
            fclose(outputFile);
        }
        return errorCode;
    }

    if(!isBMPFile(argv[2])) {// if this file isn't .bmp
        // if the file doesn't start with what all BMP files start with
        printf("File is not a valid BMP file\n");
        errorCode |= INVALID_BMP_FILE;
    }

    // read the header information from the input file
    char header[HEADER_SIZE + 1]; // this should have exactly enough space for the header plus \0
    uint rightLength = readBytesFromFile(inputFile, HEADER_SIZE, header);
    if (!(errorCode & INPUT_FILE_ERROR) && !rightLength) {
        // if the file ended before we were done reading, we have a problem
        printf("File is not a valid BMP file\n");
        errorCode |= INVALID_BMP_FILE;
    }

    // validate the header by checking the signature
    if(!(errorCode & INPUT_FILE_ERROR) && !(header[0] == 'B' && header[1] == 'M')) { // if the file doesn't have enough
        // data for a full header
        // or if the file says it's not BMP
        printf("File is not a valid BMP file\n");
        errorCode |= INVALID_BMP_FILE;
    }

    // if at this point you have errors, go no further and return the errorcode
    // (if operation, input file & output file are good, then continue)
    if (errorCode) { // if we have at least one error
        fclose(inputFile);
        if (outputFile) { // if we made the output file, close it. Otherwise, it might have errors
            fclose(outputFile);
        }
        return errorCode;
    }

    // extract the data we need from the header
    // print the image information to the stdout as below
    //  (note the hex format of data offset)
    /*
     * px width: 256
     * px height: 256
     * bit depth: 24
     * byte width: 768
     * data offset: 0x36
     */
    ImageInfo info = extractDataFromHeader(header);
    //printf("%d", info.fileSize);

    // print what you are going to do to stdout
    //  (one of the below, based on the operation)

    /*
     * Flipping the image horizontally
     * Flipping the image vertically
     * Flipping the image horizontally and vertically
     */

    declareOperation(operation);

    // write header information to the output file

    writeBytesToFile(outputFile, HEADER_SIZE, header);

    // It looks like there is some data in between the header and array
    // So I will need to put that into the array as well

    moveDataBetweenFiles(inputFile, outputFile, HEADER_SIZE, info.dataOffset);

    // Read in the image data from the input file

    // first, I will create the 2D array of pixels in memory
    // This will be used in the sense of an array of arrays, where the array slots contain pixel pointers
    // Unfortunately, it is hard to figure out how much space exactly I would need
    // I would need a number of pointers equal to length * height
    // If I get a void pointer, I could just cast it to an array of arrays of pointers
    // Or whatever I decide to store pixels as, I will probably just make each of them byte arrays
    // But those will be stored as pointers, not directly
    // I have decided that I will not be storing them as pointers, but directly in a 3d array, which is going to get really complicated

    char* bitMap = calloc(info.byteWidth * info.pxHeight + 1, sizeof(char));

    // I need to figure out what my 3D array even means
    // I want it to store each row as a block
    // Within that block, it is a sequence of pixels
    // So I should be able to read the file a row of bytes at a time for all the rows
    // There are a number of rows equal to the height
    // Great, that should work

    readBytesFromFile(inputFile, info.byteWidth * info.pxHeight, bitMap);

    //moveDataBetweenFiles(inputFile, outputFile, info.dataOffset, info.dataOffset + info.byteWidth * info.pxHeight);

    // Transform the image data in memory
    // Iterate over the pixel data and transform the image data
    // such that the image is horizontally and/or vertically flipped

    if (operation == 'H' || operation == 'B') {
        flipHorizontal(bitMap, info);
    }
    if (operation == 'V' || operation == 'B') {
        // no else, because B gives both
        flipVertical(bitMap, info);
    }

    // Write the transformed data to the output file

    writeBytesToFile(outputFile, info.byteWidth * info.pxHeight, bitMap);

    // in case there is data after the byte array I am missing
    moveDataBetweenFiles(inputFile, outputFile,  info.dataOffset + info.byteWidth * info.pxHeight, info.fileSize);

    // Release any memory

    free(bitMap);

    // Close the file handlers
    fclose(inputFile);
    fclose(outputFile);

    //printf("Hello world sanity check\n");
    return errorCode;

    // Make sure that my code works when files are where he wants them to be
    // Figured out why Diament RGBA caused problems
}

