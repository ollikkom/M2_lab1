#ifndef M2_LAB1_CASTECX_H
#define M2_LAB1_CASTECX_H
#pragma once
#include <iostream>
#include <exception>

class CastException:
        public std::exception
{
public:
    ~CastException() = default;

    CastException() : std::exception()
    {}

    CastException(const char* str) : std::exception()
    {}

};

class ExcOverflow: public CastException
{
public:
    ~ExcOverflow() = default;

    ExcOverflow() : CastException("Overflow occured")
    {}

};

class ExcSymbol: public CastException
{
public:
    ~ExcSymbol() = default;

    ExcSymbol() : CastException("Error in the symbol")
    {}


};


#endif //M2_LAB1_CASTECX_H
