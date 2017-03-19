#include <iostream>
#include "CastEcx.h"
#include <math.h>


int IntFromString(const char *data) {
    int integer = 0;
    int integer_prev = 0, i = 0;
    bool isMinus = false;
    if ( data[0] == '-')
    {
        i = 1;
        isMinus = true;
    }
    for (i; i < strlen(data); i++)
    {
        if ( data[i] > 47 && data[i] < 58)
        {
            integer = integer * 10 + (data[i] - 48);
            if (integer_prev > integer)
            {
                throw ExcOverflow();
            }
            integer_prev = integer;
        }
        else
        {
            throw ExcSymbol();
        }
    }
    if ( isMinus ) integer = -integer;
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
    float floatan_prev = 0;
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
            if (i == 0 || (i == 1 && isMinus)) {
                throw ExcSymbol();
            }
        }
        if ( dotPos != i )
        {
            if ( data[i] > 47 && data[i] < 58)
            {
                floatan = floatan * 10 + (data[i] - 48);
                if (floatan_prev > floatan)
                {
                    throw ExcOverflow();
                }
                floatan_prev = floatan;
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

    //char *test = "32hhhh";
    char* test = "3456678";

    try {
        int iS = IntFromString(test);
        std::cout << "\n" << iS << std::endl;
    }
    catch (const CastException & e){
        std::cout<< "\n" << e.what() << std::endl;
    }

    std::string testBool("false");
    const char * const s = testBool.c_str();

    try {
        bool bS = BoolFromString(s);
        std::cout <<"\n" << bS << std::endl;
    }
    catch (const CastException & e){
        std::cout << "\n"<< e.what() << std::endl;
    }

    //test = "0.223";
    //test = "-0.777757";
    test = "-.999";

    try
    {
        float fS = FloatFromString(test);
        std::cout << "\n"<< fS << std::endl;
    }
    catch (const CastException & e){
        std::cout << "\n"<< e.what() << std::endl;
    }
    return 0;
}
