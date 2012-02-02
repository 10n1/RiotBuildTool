/*
 * solution.h
 * SolutionBuilder
 *
 * Created by Kyle Weicht on 2/1/2012.
 * Copyright (c) 2012 Kyle Weicht. All rights reserved.
 */
#ifndef __SolutionBuilder_solution_h__
#define __SolutionBuilder_solution_h__

/* C headers */
/* C++ headers */
/* External headers */
/* Internal headers */
#include "project.h"

/*******************************************************************\
External Constants And types
\*******************************************************************/
struct Solution
{
    char            guid[40];
    vector<Project> projects;
};

/*******************************************************************\
External variables
\*******************************************************************/

/*******************************************************************\
External functions
\*******************************************************************/
void Generate2010Solution(const Solution& solution);

#endif /* include guard */
