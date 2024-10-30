#include <iostream>
#include <bitset>
#include <vector>
#include <ctime>
#include "funkcje.h"

using namespace std;

int main()
{

    string message = "Ala ma kota";
    vector<bitset<8>> original;
    vector<bitset<8>> cypher;
    vector<bitset<8>> interference;
    srand((unsigned) time(NULL));
    int BER = 10;
    int detectedErrors = 0;
    int unDetectedErrors = 0;
    int byteNumberWithError = 0;
    bool GBN = false;
    //tworzymy wektor w ktorym kazda pozycja to 8 bitów (jeden znak) z naszego stringa -> original
    for (size_t i = 0; i<message.size(); i++)
    {
        original.push_back(bitset<8>(message.c_str()[i]));
        cypher.push_back(bitset<8>(message.c_str()[i]));
    }

    //kodujemy wektor cypher wedlug szablonu -> nieparzysta liczba jedynek oznacza ze ostatni bit to 1 a w przeciwnym wypadku 0
    for(size_t i = 0; i<cypher.size(); i++)
    {
        if (cypher[i].count()%2==1)
        {
            cypher[i].set(7);
        }
    }


    //przesylanie metoda Stop-and-Wait (SAW) dla kanalu BSC [dla kanalu Gilberta-Elliotta wystarczy ze zmnienisz funkcje z BSC na Gilbert-Elliott)

    /*
    for (size_t i = 0; i<cypher.size(); i++)
    {
        bitset<8> temp = BSC(cypher[i], BER);
        if (temp[7]==1 && (temp.count()-1)%2==1)
        {
            interference.push_back(temp);
        }
        else if (temp[7]==0 && (temp.count())%2==0)
        {
            interference.push_back(temp);
        }
        else
        {
            i--;
            detectedErrors++;
        }

    }
    // */

    //przesyłanie metoda Go-back-N (GBN)
    /*
    while(GBN == false)
    {
        while(interference.size()!=byteNumberWithError)
        {
            interference.pop_back();
        }
        for(size_t i = 0+byteNumberWithError; i<cypher.size(); i++)
        {

            interference.push_back(BSC(cypher[i], BER));
        }


        for(size_t i = 0; i<interference.size(); i++)
        {
            if (interference[i][7]==1 && cypher[i][7]==1 && (interference[i].count()-1)%2==0)
            {
                byteNumberWithError = i;
                detectedErrors++;
                break;
            }
            else if (interference[i][7]==0 && cypher[i][7]==0 &&(interference[i].count())%2==1)
            {
                byteNumberWithError = i;
                detectedErrors++;
                break;
            }
            byteNumberWithError = -1;
        }
        if(byteNumberWithError==-1)
        {
            GBN = true;
        }
    }
    // */

    //protokół CRC8

    int8_t pol = 0x31;//liczba szesnastkowa oznacza wielomian użyty do obliczenia kodu nadmiarowego
    interference = cypher;
    interference.push_back(crc8(&cypher, pol));
    // w chwili obecnej wektor interference to tylko cypher z dodaną sumą kontrolną z algorytmu CRC
    // nie zaprogramowałem jeszcze żadnym błędów w przesyłaniu ani ich wykrywania




    //testy

    cout<<"original: ";
    for(auto i = original.begin(); i!= original.end(); i++)
    {
        cout<<"\t"<<*i;
    }
    cout<<"\n";

    cout<<"cypher: ";
    for(auto i = cypher.begin(); i!= cypher.end(); i++)
    {
        cout<<"\t"<<*i;
    }

    cout<<"\n";
    cout<<"interference: ";
    for (auto i = interference.begin(); i!= interference.end (); i++)
    {
        cout<<"\t"<<*i;
    }
    cout<<"\n";
    cout<<"detected errors: " <<detectedErrors;
}












