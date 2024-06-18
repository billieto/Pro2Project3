#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "main.h"

WAV wav;

int main(int argc, char *argv[])
{
    char *test;
    int num;

    if(argc > 6)
    {
        puts("Too many arguments");
        return 1;
    }
    else if(argc < 3)
    {
        puts("Too few arguments");
        return 1;
    }


    if(!strcmp(argv[1], "-list"))
    {
        if(argc != 3)
        {
            puts("Invalid number of arguments");
            return 1;
        }
        else if((test = strstr(argv[2], ".wav")) == NULL)
        {
            puts("Invalid argument");
            return 1;
        }

        read_header(argv[2]);
        list();
    }
    else if(!strcmp(argv[1], "-reverse"))
    {
        if(argc != 4)
        {
            puts("Invalid number of arguments");
            return 1;
        }
        else if((test = strstr(argv[2], ".wav")) == NULL)
        {
            puts("Invalid argument");
            return 1;
        }
        else if((test = strstr(argv[3], ".wav")) == NULL)
        {
            puts("Invalid argument");
            return 1;
        }

        read_header(argv[2]);
        reverse(argv[3]);
    }
    else if(!strcmp(argv[1], "-mono"))
    {
        if(argc != 4)
        {
            puts("Invalid number of arguments");
            return 1;
        }
        else if((test = strstr(argv[2], ".wav")) == NULL)
        {
            puts("Invalid argument");
            return 1;
        }
        else if((test = strstr(argv[3], ".wav")) == NULL)
        {
            puts("Invalid argument");
            return 1;
        }
    }
    else if(!strcmp(argv[1], "-crop"))
    {
        if(argc != 6)
        {
            puts("Invalid number of arguments");
            return 1;
        }
        else if((test = strstr(argv[2], ".wav")) == NULL)
        {
            puts("Invalid argument");
            return 1;
        }
        else if((test = strstr(argv[5], ".wav")) == NULL)
        {
            puts("Invalid argument");
            return 1;
        }
        else if((num = atoi(argv[3])) <= 0)
        {
            puts("Invalid argument");
            return 1;
        }
        else if((num = atoi(argv[4])) <= 0)
        {
            puts("Invalid argument");
            return 1;
        }
    }
    else
    {
        puts("Invalid argument");
        return 1;
    }

    



    return 0;
}


