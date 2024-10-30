#include "funkcje.h"


//przesylanie kanalem BSC
bitset<8> BSC (bitset<8> byte, int BER)
{

        for(int i = 0; i<8; i++)
        {
            int random = rand()% BER;
            if(random == 0)
            {
                byte.flip(i);
            }

        }
        return byte;
}
//przesylanie kanalem Gilberta-Elliotta
bitset<8> GilbertElliott(bitset<8> byte)
{
    for (size_t i = 0; i<8; i++)
    {
        double pd = 0.1;
        double pz = 0.3;
        double pdz = 0.2;
        double pzd = 0.4;
        int bitError = rand()%1000;
        int channelChange = rand()%1000;
        bool goodState;
        if (i == 0)
        {
            goodState = true;
        }
        if (goodState)
        {
            if (bitError < pd*1000)
            {
                byte.flip(i);
            }
            goodState = (channelChange>pdz*1000);
        }

        else
        {
            if (bitError <pz*1000)
            {
                byte.flip(i);
            }
            goodState = (channelChange>(1-pzd)*1000);
        }

    }
    return byte;
}
bitset<8> crc8(vector<bitset<8>> *data, int8_t polynomial)
{
    vector<bitset<8>> crc_calc = *data;
    int data_size = crc_calc.size()*8;
    crc_calc.push_back(bitset<8>());

    bitset<8> Cx = polynomial;

    for(int i = 0; i < data_size; i++)
    {
        int j = 8;

        int k = (i-(i%8))/8; //indeks bitseta w wektorze
        int l = 7-((i)%8); //indeks bitu w bitsecie

        if(crc_calc[k][l] == 1)
        {
            while(j > -1)
                {
                    if(j == 8)
                    {
                        crc_calc[k][l] = (crc_calc[k][l] ^ 1);
                    }
                    else
                    {
                        crc_calc[k][l] = (crc_calc[k][l] ^ Cx[j]); // operacja XOR
                    }

                    l--;
                    if(l == -1)
                    {
                        k++;
                        l = 7;
                    }

                    j--;
                }
        }
    }
    /*
    for (auto i = crc_calc.begin(); i!= crc_calc.end (); i++)
    {
        cout<<"\t"<<*i;
    }// */

    bitset<8> crc = crc_calc[crc_calc.size() - 1];

    return crc;
} // */
