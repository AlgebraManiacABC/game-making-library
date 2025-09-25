/********************************************************************************
 * files.c
 * 
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "files.h"

char* _gm_readEntireTextFile(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        gm_setError(ERR_CODE, ERR_NOFIL);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t fileLength = ftell(file);
    rewind(file);

    char * fileContents = malloc(fileLength + 1);
    if (!fileContents)
    {
        gm_setError(ERR_CODE, ERR_NOMEM);
        fclose(file);
        return NULL;
    }

    size_t items = fread(fileContents, 1, fileLength, file);
    if (items != fileLength)
    {
        gm_setError(ERR_MESG, "Error reading \"%s\"!", filename);
        fclose(file);
        free(fileContents);
        return NULL;
    }
    fileContents[fileLength] = '\0';
    fclose(file);

    return fileContents;
}

BinaryFile_t _gm_readEntireBinaryFile(const char* filename)
{
    BinaryFile_t binaryFile = {0, NULL};
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        gm_setError(ERR_CODE, ERR_NOFIL);
        return binaryFile;
    }

    fseek(file, 0, SEEK_END);
    size_t fileLength = ftell(file);
    rewind(file);

    byte * fileContents = malloc(fileLength + 1);
    if (!fileContents)
    {
        gm_setError(ERR_CODE, ERR_NOMEM);
        fclose(file);
        return binaryFile;
    }

    size_t items = fread(fileContents, 1, fileLength, file);
    if (items != fileLength)
    {
        gm_setError(ERR_MESG, "Error reading \"%s\"!", filename);
        fclose(file);
        free(fileContents);
        return binaryFile;
    }
    fileContents[fileLength] = '\0';
    fclose(file);

    binaryFile.fileLength = fileLength;
    binaryFile.fileData = fileContents;

    return binaryFile;
}