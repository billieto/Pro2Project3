#ifndef MAIN_H
#define MAIN_H

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

#define BYTE_SIZE sizeof(byte)
#define WORD_SIZE sizeof(word)
#define DWORD_SIZE sizeof(dword)

typedef struct RIFF_CHUNK_DESCRIPTOR
{
    dword chunkID;
    dword chunkSize;
    dword format;    
} RIFF;

typedef struct FMT_SUB_CHUNK
{
    dword subchunk1ID;
    dword subchunk1Size;
    word audioFormat;
    word numChannels;
    dword sampleRate;
    dword byteRate;
    word blockAlign;
    word bitsPerSample;
} FMT;

typedef struct DATA_SUB_CHUNK
{
    dword subchunk2ID;
    dword subchunk2Size;
    byte *data;
} DATA;

typedef struct WAV_HEADER
{
    RIFF riff;
    FMT fmt;
    DATA data;
} WAV;

extern WAV wav;
#endif