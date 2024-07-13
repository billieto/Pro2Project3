#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "main.h"

WAV wav;

int main(int argc, char *argv[])
{
    char *test;

    if(argc > 6)
    {
        puts("Too many arguments");
        puts("Please make sure you provide a valid command as of below: ");
        puts("-list <filename>");
        puts("-reverse <input> <output>");
        puts("-mono <input> <output>");
        puts("-crop <input> <output> <start> <end>");

        return 1;
    }
    else if(argc < 3)
    {
        puts("Too few arguments");
        puts("Please make sure you provide a valid command as of below: ");
        puts("-list <filename>");
        puts("-reverse <input> <output>");
        puts("-mono <input> <output>");
        puts("-crop <input> <output> <start> <end>");

        return 1;
    }

    if(!strcmp(argv[1], "-list"))
    {
        if(argc != 3)
        {
            puts("Invalid number of arguments");
            puts("Usage: ./yawn -list <filename>");

            return 1;
        }
        else if((test = strstr(argv[2], ".wav")) == NULL)
        {
            puts("Invalid argument");
            puts("Please make sure you provide a .wav file as an argument");

            return 1;
        }
        
        printf("\nReading the header of \"%s\"...\n", argv[2]);
        read_header(argv[2]);
        printf("\nReading of \"%s\", completed successfully!!\n", argv[2]);

        printf("\nListing the contents of \"%s\"...\n\n", argv[2]);
        list();
        printf("\nListing of \"%s\", completed successfully!\n", argv[2]);
    }
    else if(!strcmp(argv[1], "-reverse"))
    {
        if(argc != 4)
        {
            puts("Invalid number of arguments");
            puts("Usage: ./yawn -reverse <input> <output>");

            return 1;
        }
        else if((test = strstr(argv[2], ".wav")) == NULL)
        {
            puts("Invalid argument");
            puts("Please make sure provide a .wav file as an argument");

            return 1;
        }
        else if((test = strstr(argv[3], ".wav")) == NULL)
        {
            puts("Invalid argument");
            puts("Please make sure provide a .wav file as an argument");

            return 1;
        }

        printf("\nReading the header of \"%s\"...\n", argv[2]);
        read_header(argv[2]);
        printf("\nReading of \"%s\", completed successfully!!\n", argv[2]);

        printf("\nReversing \"%s\"...\n", argv[2]);
        reverse(argv[3]);
        printf("\nReversing completed successfully, open \"%s\" to see the result!\n", argv[3]);
    }
    else if(!strcmp(argv[1], "-mono"))
    {
        if(argc != 4)
        {
            puts("Invalid number of arguments");
            puts("Usage: ./yawn -mono <input> <output>");

            return 1;
        }
        else if((test = strstr(argv[2], ".wav")) == NULL)
        {
            puts("Invalid argument");
            puts("Please make sure you provide a .wav file as an input file");

            return 1;
        }
        else if((test = strstr(argv[3], ".wav")) == NULL)
        {
            puts("Invalid argument");
            puts("Please make sure you provide a .wav file as an output file");

            return 1;
        }

        printf("\nReading the header of \"%s\"...\n", argv[2]);
        read_header(argv[2]);
        printf("\nReading of \"%s\", completed successfully!!\n", argv[2]);

        if(wav.fmt.numChannels == 1)
        {
            printf("\n\"%s\" is already a mono audio\n", argv[2]);
            return 0;
        }
        else
        {
            printf("\nConverting \"%s\" to mono...\n", argv[2]);
            mono(argv[3]);
            printf("\nConversion completed successfully, open \"%s\" to see the result!\n", argv[3]);
        }
        
    }
    else if(!strcmp(argv[1], "-crop"))
    {
        if(argc != 6)
        {
            puts("Invalid number of arguments");
            puts("Usage: ./yawn -crop <input> <output> <start> <end>");
            return 1;
        }
        else if((test = strstr(argv[2], ".wav")) == NULL)
        {
            puts("Invalid argument");
            puts("Please make sure you provide a .wav file as an input file");

            return 1;
        }
        else if((test = strstr(argv[5], ".wav")) == NULL)
        {
            puts("Invalid argument");
            puts("Please make sure you provide a .wav file as an output file");

            return 1;
        }
        else if(atoi(argv[3]) == atoi(argv[4]))
        {
            puts("Invalid argument");
            puts("Please make sure you provide a valid start and end time");

            return 1;
        }
        else if(atoi(argv[3]) < 0 && atoi(argv[4]) < 0)
        {
            puts("Invalid argument");
            puts("Please make sure you provide a positive integer as the start and end time");

            return 1;
        }
        else if(atoi(argv[3]) < 0)
        {
            puts("Invalid argument");
            puts("Please make sure you provide a positive integer as the start time");

            return 1;
        }
        else if(atoi(argv[4]) <= 0)
        {
            puts("Invalid argument");
            puts("Please make sure you provide a positive integer as the end time");

            return 1;
        }
        else if(atoi(argv[3]) >= atoi(argv[4]))
        {
            puts("Invalid argument");
            puts("Please make sure you provide a a start time smaller than then end time");

            return 1;
        }

        printf("\nReading the header of \"%s\"...\n", argv[2]);
        read_header(argv[2]);
        printf("\nReading of \"%s\", completed successfully!!\n", argv[2]);

        printf("\nCropping \"%s\"...\n", argv[2]);
        crop(argv[5], atoi(argv[3]), atoi(argv[4]));
        printf("\nCropping completed successfully, open \"%s\" to see the result!\n", argv[5]);
    }
    else
    {
        puts("Invalid argument");
        puts("Please make sure you provide a valid command as of below: ");
        puts("-list <filename>");
        puts("-reverse <input> <output>");
        puts("-mono <input> <output>");
        puts("-crop <input> <output> <start> <end>");

        return 1;
    }

    return 0;
}