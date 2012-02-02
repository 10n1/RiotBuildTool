/*
 * utility.h
 * SolutionBuilder
 *
 * Created by Kyle Weicht on 2/1/2012.
 * Copyright (c) 2012 Kyle Weicht. All rights reserved.
 */
#ifndef __SolutionBuilder_utility_h__
#define __SolutionBuilder_utility_h__

/* C headers */
/* C++ headers */
/* External headers */
/* Internal headers */

/*******************************************************************\
External Constants And types
\*******************************************************************/

/*******************************************************************\
External variables
\*******************************************************************/

/*******************************************************************\
External functions
\*******************************************************************/
void GenerateGUID(char guid[39])
{
    guid[0]  = '{';
    guid[37] = '}';
    guid[38] = '\0';

    char* writePos = guid+1;
    int writeIndex = 1;
    while(*writePos != '}')
    {
        if (writeIndex == 9 || writeIndex == 14 || writeIndex == 19 || writeIndex == 24)
        {
            *writePos = '-';
        }
        else
        {
            char digit = rand()%16;
            if(digit < 10)
            {
                digit += '0';
            }
            else
            {
                digit = (digit-10)+'A';
            }

            *writePos = digit;
        }

        ++writeIndex;
        ++writePos;
    }
}

#endif /* include guard */
