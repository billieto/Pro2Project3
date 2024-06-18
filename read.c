#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "main.h"

void read_header(char *filename)
{
    FILE *audio;

    audio = fopen(filename, "rb");
    check_file(audio);

    // riff chunk
    fread(&wav.riff.chunkID, DWORD_SIZE, 1, audio);
    fread(&wav.riff.chunkSize, DWORD_SIZE, 1, audio);
    fread(&wav.riff.format, DWORD_SIZE, 1, audio);

    // fmt subchunk
    fread(&wav.fmt.subchunk1ID, DWORD_SIZE, 1, audio);
    fread(&wav.fmt.subchunk1Size, DWORD_SIZE, 1, audio);
    fread(&wav.fmt.audioFormat, WORD_SIZE, 1, audio);
    fread(&wav.fmt.numChannels, WORD_SIZE, 1, audio);
    fread(&wav.fmt.sampleRate, DWORD_SIZE, 1, audio);
    fread(&wav.fmt.byteRate, DWORD_SIZE, 1, audio);
    fread(&wav.fmt.blockAlign, WORD_SIZE, 1, audio);
    fread(&wav.fmt.bitsPerSample, WORD_SIZE, 1, audio);

    // data subchunk
    fread(&wav.data.subchunk2ID, DWORD_SIZE, 1, audio);
    fread(&wav.data.subchunk2Size, DWORD_SIZE, 1, audio);
    wav.data.data = (byte*) malloc(wav.data.subchunk2Size * BYTE_SIZE);
    fread(wav.data.data, wav.data.subchunk2Size, 1, audio);

    fclose(audio);
}

void write_header(WAV new, char *filename)
{
    FILE *audio;

    audio = fopen(filename, "wb");
    check_file(audio);

    // riff chunk
    fwrite(&new.riff.chunkID, DWORD_SIZE, 1, audio);
    fwrite(&new.riff.chunkSize, DWORD_SIZE, 1, audio);
    fwrite(&new.riff.format, DWORD_SIZE, 1, audio);

    // fmt subchunk
    fwrite(&new.fmt.subchunk1ID, DWORD_SIZE, 1, audio);
    fwrite(&new.fmt.subchunk1Size, DWORD_SIZE, 1, audio);
    fwrite(&new.fmt.audioFormat, WORD_SIZE, 1, audio);
    fwrite(&new.fmt.numChannels, WORD_SIZE, 1, audio);
    fwrite(&new.fmt.sampleRate, DWORD_SIZE, 1, audio);
    fwrite(&new.fmt.byteRate, DWORD_SIZE, 1, audio);
    fwrite(&new.fmt.blockAlign, WORD_SIZE, 1, audio);
    fwrite(&new.fmt.bitsPerSample, WORD_SIZE, 1, audio);

    // data subchunk
    fwrite(&new.data.subchunk2ID, DWORD_SIZE, 1, audio);
    fwrite(&new.data.subchunk2Size, DWORD_SIZE, 1, audio);
    fwrite(new.data.data, new.data.subchunk2Size, 1, audio);
    free(new.data.data);

    fclose(audio);
}

void list(void)
{
    puts("RIFF_CHUNK_HEADER");
    puts("=================");
    printf("chunkID: ");
    print_bytes(&wav.riff.chunkID, DWORD_SIZE);
    printf("chunkSize: %d\n", wav.riff.chunkSize);
    printf("format: ");
    print_bytes(&wav.riff.format, DWORD_SIZE);
    putchar('\n');
    puts("FMT_SUBCHUNK_HEADER");
    puts("===================");
    printf("subchunk1ID: ");
    print_bytes(&wav.fmt.subchunk1ID, DWORD_SIZE);
    printf("subchunk1Size: %d\n", wav.fmt.subchunk1Size);
    printf("audioFormat: %d\n", wav.fmt.audioFormat);
    printf("numChannels: %d\n", wav.fmt.numChannels);
    printf("sampleRate: %d\n", wav.fmt.sampleRate);
    printf("byteRate: %d\n", wav.fmt.byteRate);
    printf("blockAlign: %d\n", wav.fmt.blockAlign);
    printf("bitsPerSample: %d\n\n", wav.fmt.bitsPerSample);
    puts("DATA_SUBCHUNK_HEADER");
    puts("====================");
    printf("subchunk2ID: ");
    print_bytes(&wav.data.subchunk2ID, DWORD_SIZE);
    printf("subchunk2Size: %d\n", wav.data.subchunk2Size);
}

void reverse(char *output)
{
    dword i = 0;
    dword j = 0;
    dword temp, left, right;

    for(i = 0; i < wav.data.subchunk2Size / 2; i++)
    {
        temp = wav.data.data[i];
        wav.data.data[i] = wav.data.data[wav.data.subchunk2Size - i - 1];
        wav.data.data[wav.data.subchunk2Size - i - 1] = temp;
    }

    write_header(wav, output);
}

void mono(char *output)
{
    FILE *mono;

    mono = fopen(output, "wb");
    check_file(mono);



    fclose(mono);
}

void print_bytes(dword *var, dword size)
{
    dword i;

    byte *byte_ptr = (byte*) var;

    for(i = 0; i < size; i++)
    {
        printf("%C", byte_ptr[i]);
    }
    putchar('\n');
}

dword swap_32bit(dword val)
{
    return ((val >> 24) & 0x000000FF) |
           ((val >> 8)  & 0x0000FF00) |
           ((val << 8)  & 0x00FF0000) |
           ((val << 24) & 0xFF000000);
}

void check_file(FILE *wav)
{
    if(wav == NULL)
    {
        puts("Error opening file");
        exit(EXIT_FAILURE);
    }
}

void check_malloc(void *ptr)
{
    if(ptr == NULL)
    {
        puts("Error allocating memory");
        exit(EXIT_FAILURE);
    }
}