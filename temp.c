    while(i < loop / 2)
    {
        if(i != 0)
        {
            i++;
        }

        for(j = k; j > k - wav.fmt.blockAlign + 1; j--)
        {
            temp = wav.data.data[i];
            wav.data.data[i] = wav.data.data[wav.data.subchunk2Size - j];
            wav.data.data[wav.data.subchunk2Size - j] = temp;
            i++;
        }
        k += wav.fmt.blockAlign;
    }