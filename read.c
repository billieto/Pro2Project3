#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "main.h"

void read_header(char *filename)
{
    FILE *audio;
    char *temp;

    audio = fopen(filename, "rb");
    check_file(audio);

    // riff chunk
    fread(&wav.riff.chunkID, DWORD_SIZE, 1, audio);

    temp = (char*) malloc(5 * CHAR_SIZE); // to check if the file is a wav file
    memcpy(temp, &wav.riff.chunkID, DWORD_SIZE); // i use memcpy insted of strdup or strcpy because BYTE is unsinged char and want to be sure
    temp[4] = '\0'; // to make it a string
    if(strcmp(temp, "RIFF"))
    {
        puts("Invalid file format!");
        puts("RIFF ChunkID section invalid!");
        puts("Terminating Program...");
        free(temp);
        fclose(audio);
        exit(EXIT_FAILURE);
    }
    free(temp);

    fread(&wav.riff.chunkSize, DWORD_SIZE, 1, audio);
    fread(&wav.riff.format, DWORD_SIZE, 1, audio);

    temp = (char*) malloc(5 * CHAR_SIZE); // to check if the file is a wav file
    memcpy(temp, &wav.riff.format, DWORD_SIZE);
    temp[4] = '\0'; // to make it a string
    if(strcmp(temp, "WAVE"))
    {
        puts("Invalid file format!");
        puts("RIFF Format section invalid!");
        puts("Terminating Program...");
        free(temp);
        fclose(audio);
        exit(EXIT_FAILURE);
    }
    free(temp);

    // fmt subchunk
    fread(&wav.fmt.subchunk1ID, DWORD_SIZE, 1, audio);

    temp = (char*) malloc(5 * CHAR_SIZE); // to check if the file is a wav file
    memcpy(temp, &wav.fmt.subchunk1ID, DWORD_SIZE);
    temp[4] = '\0'; // to make it a string
    if(strcmp(temp, "fmt "))
    {
        puts("Invalid file format!");
        puts("FMT Subchunk1ID section invalid!");
        puts("Terminating Program...");
        free(temp);
        fclose(audio);
        exit(EXIT_FAILURE);
    }
    free(temp);

    fread(&wav.fmt.subchunk1Size, DWORD_SIZE, 1, audio);
    fread(&wav.fmt.audioFormat, WORD_SIZE, 1, audio);

    if(wav.fmt.audioFormat != 1)
    {
        puts("Invalid file format!");
        puts("Audio format not supported!");
        puts("Terminating Program...");
        fclose(audio);
        exit(EXIT_FAILURE);
    }

    fread(&wav.fmt.numChannels, WORD_SIZE, 1, audio);

    if(wav.fmt.numChannels != 1 && wav.fmt.numChannels != 2)
    {
        puts("Invalid file format!");
        puts("Number of channels not supported!");
        puts("Terminating Program...");
        fclose(audio);
        exit(EXIT_FAILURE);
    }

    fread(&wav.fmt.sampleRate, DWORD_SIZE, 1, audio);
    fread(&wav.fmt.byteRate, DWORD_SIZE, 1, audio);
    fread(&wav.fmt.blockAlign, WORD_SIZE, 1, audio);
    fread(&wav.fmt.bitsPerSample, WORD_SIZE, 1, audio);

    // data subchunk
    fread(&wav.data.subchunk2ID, DWORD_SIZE, 1, audio);

    temp = (char*) malloc(5 * CHAR_SIZE); // to check if the file is a wav file
    memcpy(temp, &wav.data.subchunk2ID, DWORD_SIZE);
    temp[4] = '\0'; // to make it a string
    if(strcmp(temp, "data"))
    {
        puts("Invalid file format!");
        puts("data SubChunk2ID section invalid!");
        puts("Terminating Program...");
        free(temp);
        fclose(audio);
        exit(EXIT_FAILURE);
    }
    free(temp);

    fread(&wav.data.subchunk2Size, DWORD_SIZE, 1, audio);
    wav.data.data = (byte*) malloc(wav.data.subchunk2Size * BYTE_SIZE);
    fread(wav.data.data, wav.data.subchunk2Size, 1, audio);

    fclose(audio);
}

void write_header(char *filename)
{
    FILE *audio;

    audio = fopen(filename, "wb");
    check_file(audio);

    // riff chunk
    fwrite(&wav.riff.chunkID, DWORD_SIZE, 1, audio);
    fwrite(&wav.riff.chunkSize, DWORD_SIZE, 1, audio);
    fwrite(&wav.riff.format, DWORD_SIZE, 1, audio);

    // fmt subchunk
    fwrite(&wav.fmt.subchunk1ID, DWORD_SIZE, 1, audio);
    fwrite(&wav.fmt.subchunk1Size, DWORD_SIZE, 1, audio);
    fwrite(&wav.fmt.audioFormat, WORD_SIZE, 1, audio);
    fwrite(&wav.fmt.numChannels, WORD_SIZE, 1, audio);
    fwrite(&wav.fmt.sampleRate, DWORD_SIZE, 1, audio);
    fwrite(&wav.fmt.byteRate, DWORD_SIZE, 1, audio);
    fwrite(&wav.fmt.blockAlign, WORD_SIZE, 1, audio);
    fwrite(&wav.fmt.bitsPerSample, WORD_SIZE, 1, audio);

    // data subchunk
    fwrite(&wav.data.subchunk2ID, DWORD_SIZE, 1, audio);
    fwrite(&wav.data.subchunk2Size, DWORD_SIZE, 1, audio);
    fwrite(wav.data.data, wav.data.subchunk2Size, 1, audio);
    free(wav.data.data);

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
    dword i = 0, j = 0, frames = wav.data.subchunk2Size / wav.fmt.blockAlign; // frames is the number of samples in the audio
    byte *temp = (byte*) malloc(wav.fmt.blockAlign); // temporary allocation for the reversed audio

    for(i = 0; i < frames / 2; i++) // we only need to go through half of the audio to reverse it
    {
        j = frames - i - 1; // we have to start from the end of the audio

        // now we basicly move the audio from the end to the beginning based on the the number of bytes in one block (blockalign) for the reversed audio to be right
        memcpy(temp, &wav.data.data[i * wav.fmt.blockAlign], wav.fmt.blockAlign);
        memcpy(&wav.data.data[i * wav.fmt.blockAlign], &wav.data.data[j * wav.fmt.blockAlign], wav.fmt.blockAlign);
        memcpy(&wav.data.data[j * wav.fmt.blockAlign], temp, wav.fmt.blockAlign);
    }
    
    free(temp);

    write_header(output);
}

void mono(char *output)
{
    
}

void crop(char *output, int start, int end)
{

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