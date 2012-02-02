/*
 * project.h
 * SolutionBuilder
 *
 * Created by Kyle Weicht on 2/1/2012.
 * Copyright (c) 2012 Kyle Weicht. All rights reserved.
 */
#ifndef __SolutionBuilder_project_h__
#define __SolutionBuilder_project_h__

/* C headers */
/* C++ headers */
#include <string>
#include <vector>
/* External headers */
/* Internal headers */

using std::string;
using std::vector;

/*******************************************************************\
External Constants And types
\*******************************************************************/
enum ProjectType
{
    kCommandLine,
    kApplication,
    kStaticLib,
    kDynamicLib,
};
struct Project
{
    char    guid[40];
    string  name;
    string  targetDir;
    string  targetName;

    ProjectType type;
    vector<string>  sourceFiles;
    vector<string>  headerFiles;

    vector<string>  defines;
    vector<string>  includeDirs;

    bool    warningsAsErrors;
    bool    enableExceptions;
    bool    enableRTTI;
};

/*******************************************************************\
External variables
\*******************************************************************/

/*******************************************************************\
External functions
\*******************************************************************/
void GenerateVS2010Project(const Project& project);

#endif /* include guard */
