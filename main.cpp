#include <iostream>
#include "CastEcx.h"
#include <math.h>
#include <limits>

int NumS(const char symb)
{
    if (symb >= 48 && symb <= 57)
        return symb - 48;
    else
        throw ExcSymbol();
}

int IntFromString(const char *data) {
    if (data == "")
        throw ExcSymbol();
    int integer = 0;
    int sizeMax = 10;
    bool isMinus = false;
    int i = 0;
    if (data[0] == '-') {
        isMinus = true;
        i = 1;
    }
    while (data[i] == '0') {
        ++i;
    }
    if (strlen(data) - i > 10)
        throw ExcOverflow();
    else {
        if (strlen(data) - i == 10) {
            if (NumS(data[i]) > 2)
                throw ExcOverflow();
        }
        for (i; i < strlen(data); ++i) {
            if (isMinus) {
                integer = integer * 10 - NumS(data[i]);
                if (integer > 0)
                    throw ExcOverflow();
            }
            else {
                integer = integer * 10 + NumS(data[i]);
                if (integer < 0)
                    throw ExcOverflow();
            }
        }
    }
    return integer;
}

bool BoolFromString(const char *data) {
    if (strcmp(data, "false") == 0)
        return false;
    else if (strcmp(data, "true") == 0)
        return true;
    else
        throw ExcSymbol();

}

float FloatFromString(const char *data) {
    float floatan = 0;
    int dotPos = -1, i = 0;
    bool isMinus = false;
    if ( data[0] == '-')
    {
        i = 1;
        isMinus = true;
    }
    for (i; i < strlen(data); i++)
    {
        if ( data[i] == '.' )
        {
            if ( dotPos != -1 )
            {
                throw ExcSymbol();
            }
            dotPos = i;
            if (i == 0 || (i == 1 && isMinus))
            {
                throw ExcSymbol();
            }
        }
        if ( dotPos != i )
        {
            if ( data[i] > 47 && data[i] < 58)
            {
                floatan = floatan * 10 + (data[i] - 48);
                if (floatan > std::numeric_limits<float>::max())
                {
                    throw ExcOverflow();
                }
            }
            else
            {
                throw ExcSymbol();
            }
        }
    }
    floatan *= pow(0.1, strlen(data) - dotPos - 1);
    if ( isMinus ) floatan = -floatan;
    return floatan;
}


int main() {

    try {
        //char* test = "32hhhh";
        //char* test = "3456678";
        char* test = "-2147483648";

        int iS = IntFromString(test);
        std::cout << "\n" << iS << std::endl;
    }
    catch (const CastException & e){
        std::cout<< "\n" << e.what() << std::endl;
    }


    try {
        char* s = "false";
        bool bS = BoolFromString(s);
        std::cout <<"\n" << bS << std::endl;
    }
    catch (const CastException & e){
        std::cout << "\n"<< e.what() << std::endl;
    }


    try
    {   //char* test = "0.223";
        //char* test = "-0.777757";
        //char* test = "-.999";
        char* test = "83999967";
        //char* test = "-0.888";
        float fS = FloatFromString(test);
        std::cout << "\n"<< fS << std::endl;
    }
    catch (const CastException & e){
        std::cout << "\n"<< e.what() << std::endl;
    }
    return 0;
}
