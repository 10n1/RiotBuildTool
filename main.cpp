/*
 * main.cpp
 * PROJECTNAME
 *
 * Created by Kyle Weicht on 2/1/2012.
 * Copyright (c) 2012 Kyle Weicht. All rights reserved.
 */

/* C headers */
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* C++ headers */
/* External headers */
/* Internal headers */
#include "project.h"
#include "utility.h"

namespace
{

/*******************************************************************\
Internal Constants And types
\*******************************************************************/

/*******************************************************************\
Internal variables
\*******************************************************************/
Project testProject;

/*******************************************************************\
Internal functions
\*******************************************************************/
void BuildProjectStruct(void)
{
    GenerateGUID(testProject.guid);

    testProject.name = "TestProjectName";
    testProject.targetDir = "MyOutputDir/";
    testProject.targetName = "MyExeName";

    testProject.type = kApplication;
    testProject.sourceFiles.push_back("testsource11.cpp");
    testProject.sourceFiles.push_back("testsource12.cpp");
    testProject.sourceFiles.push_back("testsource13.cpp");
    testProject.sourceFiles.push_back("testsource14.cpp");
    testProject.headerFiles.push_back("testsource11.h");
    testProject.headerFiles.push_back("testsource12.h");
    testProject.headerFiles.push_back("testsource13.h");
    testProject.headerFiles.push_back("testsource14.h");
    testProject.defines.push_back("MYDEFINE_1");
    testProject.defines.push_back("MYDEFINE_2");
    testProject.defines.push_back("MYDEFINE_3");
    testProject.defines.push_back("MYDEFINE_4");
}

} // anonymous namespace

/*******************************************************************\
External variables
\*******************************************************************/

/*******************************************************************\
External functions
\*******************************************************************/
int main(int argc, char* argv[])
{
    srand(time(NULL));

    BuildProjectStruct();
    GenerateVS2010Project(testProject);
    return 0;
}

