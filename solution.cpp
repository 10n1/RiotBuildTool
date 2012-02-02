/*
 * solution.cpp
 * SolutionBuilder
 *
 * Created by Kyle Weicht on 2/1/2012.
 * Copyright (c) 2012 Kyle Weicht. All rights reserved.
 */

#include "solution.h"

/* C headers */
/* C++ headers */
/* External headers */
/* Internal headers */

namespace
{

/*******************************************************************\
Internal Constants And types
\*******************************************************************/

/*******************************************************************\
Internal variables
\*******************************************************************/

/*******************************************************************\
Internal functions
\*******************************************************************/

} // anonymous namespace

/*******************************************************************\
External variables
\*******************************************************************/

/*******************************************************************\
External functions
\*******************************************************************/
void Generate2010Solution(const Solution& solution)
{
    std::string solutionString;

    solutionString += "Microsoft Visual Studio Solution File, Format Version 11.00\n# Visual Studio 2010\n";
    for(int ii=0; ii<solution.projects.size(); ++ii)
    {
        const Project& project = solution.projects[ii];
        solutionString += "Project(\"";
        solutionString += solution.guid;
        solutionString += "\") = \"" + project.name + "\", \"" + project.projectFilename + "\", \"";
        solutionString += project.guid;
        solutionString += "\"\n";
        solutionString += "EndProject\n";
    }
}

