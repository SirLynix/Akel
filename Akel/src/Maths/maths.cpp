// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 09/04/2022

#include <Maths/maths.h>

namespace Ak::Maths
{
    int randint(int a, int b)
    {
        return rand() % (b - a) + a;
    }

    bool rand_probability(double proba)
    {
        if(proba < 1)
            return ((double)rand() / (double)RAND_MAX < proba);
        else if(proba >= 1)
            return true;
        return false;
    }

    float rsqrt(float number) // A Quake III algorithm
    {
        float y = number;
        long i = *(long*)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float*)&i;
        return y * (1.5f - ((number * 0.5f) * y * y));
    }

    float fsqrt(float number)
    {
        float y = number;
        long i = *(long*)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float*)&i;
        return y * (1.5f - ((number * 0.5f) * y * y));
    }
}
