/********************************************************************************
 * files.h
 * 
 ********************************************************************************/

#ifndef LLGML_FILES_H
#define LLGML_FILES_H

#include <stdint.h>
#include "debug.h"
typedef uint8_t byte;

typedef struct BinaryFile_s
{
    size_t fileLength;
    byte * fileData;

}   BinaryFile_t;

/**
 * Takes a plaintext file and reads it to a char *.
 * It is assumed that this file does not contain null characters.
 *
 * @param filename The name of the plaintext file to read
 * @return the text of the file in string format
 */
NODISCARD
char * _gm_readEntireTextFile(const char* filename);

/**
 * Takes a binary file and reads it to a BinaryFile type.
 *
 * @param filename The name of the binary file to read
 * @return the contents of the file as a `BinaryFile_t`, including its file length.
 * If the file length is <= 0, there was an issue reading the file.
 */
NODISCARD
BinaryFile_t _gm_readEntireBinaryFile(const char* filename);

#endif //LLGML_FILES_H