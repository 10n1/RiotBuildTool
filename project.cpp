/*
 * project.cpp
 * PROJECTNAME
 *
 * Created by Kyle Weicht on 2/1/2012.
 * Copyright (c) 2012 Kyle Weicht. All rights reserved.
 */

#include "project.h"

/* C headers */
/* C++ headers */
#include <fstream>
#include <string>
/* External headers */
/* Internal headers */

/*
 * Define debugBreak
 */
#if defined( _MSC_VER )
    #define debugBreak() __debugbreak()
#elif defined( __GNUC__ )
    #define debugBreak() __asm__( "int $3\n" : : )
#else
    #error Unsupported compiler
#endif

/*
 * Define assert
 */
#ifndef assert
    #define assert(condition)   \
        do                      \
        {                       \
            if(!(condition))    \
            {                   \
                debugBreak();   \
            }                   \
        } while(__LINE__ == -1)
        /* This causes warning 4127 with VC++ (conditional expression is constant) */
    #if defined( _MSC_VER )
        #pragma warning(disable:4127)
    #endif /* defined( _MSC_VER ) */
#endif

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
void GenerateVS2010Project(const Project& project)
{
    std::string warningsAsErrors = project.warningsAsErrors ? "true" : "false";
    std::string RTTI = project.enableRTTI ? "true" : "false";
    std::string exceptions = project.enableExceptions ? "true" : "false";
    std::string includeDirs;
    for(int ii=0; ii<project.includeDirs.size(); ++ii)
    {
        includeDirs += project.includeDirs[ii] + ';';
    }
    std::string defines;
    for(int ii=0; ii<project.defines.size(); ++ii)
    {
        includeDirs += project.defines[ii] + ';';
    }

    std::string projectType;
    std::string subsystem;
    switch(project.type)
    {
    case kCommandLine:
        subsystem = "Console";
        projectType = "Application"; break;
    case kApplication:  
        subsystem = "Windows";
        projectType = "Application"; break;
    case kStaticLib:    
        subsystem = "Windows";
        projectType = "StaticLibrary"; break;
    case kDynamicLib:   
        subsystem = "Windows";
        projectType = "DynamicLibrary"; break;
    default: assert(0); break;
    }

    std::string projectString;

    // Basic project configuration
    projectString += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    projectString += "<Project DefaultTargets=\"Build\" ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n";
    projectString += "  <ItemGroup Label=\"ProjectConfigurations\">\n";
    projectString += "  <ProjectConfiguration Include=\"Debug|Win32\">\n";
    projectString += "    <Configuration>Debug</Configuration>\n";
    projectString += "    <Platform>Win32</Platform>\n";
    projectString += "  </ProjectConfiguration>\n";
    projectString += "  <ProjectConfiguration Include=\"Debug|x64\">\n";
    projectString += "    <Configuration>Debug</Configuration>\n";
    projectString += "    <Platform>x64</Platform>\n";
    projectString += "  </ProjectConfiguration>\n";
    projectString += "  <ProjectConfiguration Include=\"Release|Win32\">\n";
    projectString += "    <Configuration>Release</Configuration>\n";
    projectString += "    <Platform>Win32</Platform>\n";
    projectString += "  </ProjectConfiguration>\n";
    projectString += "  <ProjectConfiguration Include=\"Release|x64\">\n";
    projectString += "    <Configuration>Release</Configuration>\n";
    projectString += "    <Platform>x64</Platform>\n";
    projectString += "  </ProjectConfiguration>\n";
    projectString += "  </ItemGroup>\n";

    // Include files
    projectString += "  <ItemGroup>\n";
    for(int ii=0; ii<project.headerFiles.size(); ++ii)
    {
        projectString += "    <ClInclude Include=\"";
        projectString += project.headerFiles[ii];
        projectString += "\"/>\n";
    }
    projectString += "  </ItemGroup>\n";
    
    // Source files
    projectString += "  <ItemGroup>\n";
    for(int ii=0; ii<project.sourceFiles.size(); ++ii)
    {
        projectString += "    <ClCompile Include=\"";
        projectString += project.sourceFiles[ii];
        projectString += "\"/>\n";
    }
    projectString += "  </ItemGroup>\n";
    
    // Global
    projectString += "  <PropertyGroup Label=\"Globals\">\n";
    projectString += "    <ProjectGuid>";
    projectString += project.guid;
    projectString += "  </ProjectGuid>\n";
    projectString += "    <Keyword>Win32Proj</Keyword>\n";
    projectString += "    <RootNamespace>" + project.name + "</RootNamespace>\n";
    projectString += "  </PropertyGroup>\n";

    // General settings
    projectString += "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\" />\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\" Label=\"Configuration\">\n";
    projectString += "    <ConfigurationType>" + projectType + "</ConfigurationType>\n";
    projectString += "    <UseDebugLibraries>true</UseDebugLibraries>\n";
    projectString += "    <CharacterSet>NotSet</CharacterSet>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\" Label=\"Configuration\">\n";
    projectString += "    <ConfigurationType>" + projectType + "</ConfigurationType>\n";
    projectString += "    <UseDebugLibraries>true</UseDebugLibraries>\n";
    projectString += "    <CharacterSet>NotSet</CharacterSet>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\" Label=\"Configuration\">\n";
    projectString += "    <ConfigurationType>" + projectType + "</ConfigurationType>\n";
    projectString += "    <UseDebugLibraries>false</UseDebugLibraries>\n";
    projectString += "    <WholeProgramOptimization>true</WholeProgramOptimization>\n";
    projectString += "    <CharacterSet>NotSet</CharacterSet>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\" Label=\"Configuration\">\n";
    projectString += "    <ConfigurationType>" + projectType + "</ConfigurationType>\n";
    projectString += "    <UseDebugLibraries>false</UseDebugLibraries>\n";
    projectString += "    <WholeProgramOptimization>true</WholeProgramOptimization>\n";
    projectString += "    <CharacterSet>NotSet</CharacterSet>\n";
    projectString += "  </PropertyGroup>\n";

    // More settings...
    projectString += "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" />\n";
    projectString += "  <ImportGroup Label=\"ExtensionSettings\">\n";
    projectString += "  </ImportGroup>\n";
    projectString += "  <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">\n";
    projectString += "    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />\n";
    projectString += "  </ImportGroup>\n";
    projectString += "  <ImportGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\" Label=\"PropertySheets\">\n";
    projectString += "    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />\n";
    projectString += "  </ImportGroup>\n";
    projectString += "  <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">\n";
    projectString += "    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />\n";
    projectString += "  </ImportGroup>\n";
    projectString += "  <ImportGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\" Label=\"PropertySheets\">\n";
    projectString += "    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />\n";
    projectString += "  </ImportGroup>\n";
    projectString += "  <PropertyGroup Label=\"UserMacros\" />\n";

    // Output directory
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">\n";
    projectString += "    <OutDir>" + project.targetDir + "/bin/</OutDir>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">\n";
    projectString += "    <OutDir>" + project.targetDir + "/bin/</OutDir>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">\n";
    projectString += "    <IntDir>" + project.targetDir + "/obj/</IntDir>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">\n";
    projectString += "    <IntDir>" + project.targetDir + "/obj/</IntDir>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">\n";
    projectString += "    <OutDir>" + project.targetDir + "/bin/</OutDir>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">\n";
    projectString += "    <OutDir>" + project.targetDir + "/bin/</OutDir>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">\n";
    projectString += "    <IntDir>" + project.targetDir + "/obj/</IntDir>\n";
    projectString += "  </PropertyGroup>\n";
    projectString += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">\n";
    projectString += "    <IntDir>" + project.targetDir + "/obj/</IntDir>\n";
    projectString += "  </PropertyGroup>\n";

    // Build settings
    projectString += "  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">\n";
    projectString += "    <ClCompile>\n";
    projectString += "      <PrecompiledHeader>\n";
    projectString += "      </PrecompiledHeader>\n";
    projectString += "      <WarningLevel>Level4</WarningLevel>\n";
    projectString += "      <Optimization>Disabled</Optimization>\n";
    projectString += "      <PreprocessorDefinitions>" + defines + "WIN32;_DEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>\n";
    projectString += "      <AdditionalIncludeDirectories>" + includeDirs + "</AdditionalIncludeDirectories>\n";
    projectString += "      <TreatWarningAsError>" + warningsAsErrors + "</TreatWarningAsError>\n";
    projectString += "      <MultiProcessorCompilation>true</MultiProcessorCompilation>\n";
    projectString += "      <MinimalRebuild>false</MinimalRebuild>\n";
    projectString += "      <ExceptionHandling>" + exceptions + "</ExceptionHandling>\n";
    projectString += "      <BasicRuntimeChecks>Default</BasicRuntimeChecks>\n";
    projectString += "      <RuntimeTypeInfo>" + RTTI + "</RuntimeTypeInfo>\n";
    projectString += "    </ClCompile>\n";
    projectString += "    <Link>\n";
    projectString += "      <SubSystem>" + subsystem + "/SubSystem>\n";
    projectString += "      <GenerateDebugInformation>true</GenerateDebugInformation>\n";
    projectString += "    </Link>\n";
    projectString += "  </ItemDefinitionGroup>\n";
    projectString += "  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">\n";
    projectString += "    <ClCompile>\n";
    projectString += "      <PrecompiledHeader>\n";
    projectString += "      </PrecompiledHeader>\n";
    projectString += "      <WarningLevel>Level4</WarningLevel>\n";
    projectString += "      <Optimization>Disabled</Optimization>\n";
    projectString += "      <PreprocessorDefinitions>" + defines + "WIN32;_DEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>\n";
    projectString += "      <AdditionalIncludeDirectories>" + includeDirs + "</AdditionalIncludeDirectories>\n";
    projectString += "      <TreatWarningAsError>" + warningsAsErrors + "</TreatWarningAsError>\n";
    projectString += "      <MultiProcessorCompilation>true</MultiProcessorCompilation>\n";
    projectString += "      <MinimalRebuild>false</MinimalRebuild>\n";
    projectString += "      <ExceptionHandling>" + exceptions + "</ExceptionHandling>\n";
    projectString += "      <BasicRuntimeChecks>Default</BasicRuntimeChecks>\n";
    projectString += "      <RuntimeTypeInfo>" + RTTI + "</RuntimeTypeInfo>\n";
    projectString += "    </ClCompile>\n";
    projectString += "    <Link>\n";
    projectString += "      <SubSystem>" + subsystem + "/SubSystem>\n";
    projectString += "      <GenerateDebugInformation>true</GenerateDebugInformation>\n";
    projectString += "    </Link>\n";
    projectString += "  </ItemDefinitionGroup>\n";
    projectString += "  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">\n";
    projectString += "    <ClCompile>\n";
    projectString += "      <WarningLevel>Level4</WarningLevel>\n";
    projectString += "      <PrecompiledHeader>\n";
    projectString += "      </PrecompiledHeader>\n";
    projectString += "      <Optimization>MaxSpeed</Optimization>\n";
    projectString += "      <FunctionLevelLinking>true</FunctionLevelLinking>\n";
    projectString += "      <IntrinsicFunctions>true</IntrinsicFunctions>\n";
    projectString += "      <PreprocessorDefinitions>" + defines + "WIN32;NDEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>\n";
    projectString += "      <AdditionalIncludeDirectories>" + includeDirs + "</AdditionalIncludeDirectories>\n";
    projectString += "      <TreatWarningAsError>" + warningsAsErrors + "</TreatWarningAsError>\n";
    projectString += "      <MultiProcessorCompilation>true</MultiProcessorCompilation>\n";
    projectString += "      <MinimalRebuild>false</MinimalRebuild>\n";
    projectString += "      <ExceptionHandling>" + exceptions + "</ExceptionHandling>\n";
    projectString += "      <BasicRuntimeChecks>Default</BasicRuntimeChecks>\n";
    projectString += "      <RuntimeTypeInfo>" + RTTI + "</RuntimeTypeInfo>\n";
    projectString += "    </ClCompile>\n";
    projectString += "    <Link>\n";
    projectString += "      <SubSystem>" + subsystem + "/SubSystem>\n";
    projectString += "      <GenerateDebugInformation>true</GenerateDebugInformation>\n";
    projectString += "      <EnableCOMDATFolding>true</EnableCOMDATFolding>\n";
    projectString += "      <OptimizeReferences>true</OptimizeReferences>\n";
    projectString += "    </Link>\n";
    projectString += "  </ItemDefinitionGroup>\n";
    projectString += "  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">\n";
    projectString += "    <ClCompile>\n";
    projectString += "      <WarningLevel>Level4</WarningLevel>\n";
    projectString += "      <PrecompiledHeader>\n";
    projectString += "      </PrecompiledHeader>\n";
    projectString += "      <Optimization>MaxSpeed</Optimization>\n";
    projectString += "      <FunctionLevelLinking>true</FunctionLevelLinking>\n";
    projectString += "      <IntrinsicFunctions>true</IntrinsicFunctions>\n";
    projectString += "      <PreprocessorDefinitions>" + defines + "WIN32;NDEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>\n";
    projectString += "      <AdditionalIncludeDirectories>" + includeDirs + "</AdditionalIncludeDirectories>\n";
    projectString += "      <TreatWarningAsError>" + warningsAsErrors + "</TreatWarningAsError>\n";
    projectString += "      <MultiProcessorCompilation>true</MultiProcessorCompilation>\n";
    projectString += "      <MinimalRebuild>false</MinimalRebuild>\n";
    projectString += "      <ExceptionHandling>" + exceptions + "</ExceptionHandling>\n";
    projectString += "      <BasicRuntimeChecks>Default</BasicRuntimeChecks>\n";
    projectString += "      <RuntimeTypeInfo>" + RTTI + "</RuntimeTypeInfo>\n";
    projectString += "    </ClCompile>\n";
    projectString += "    <Link>\n";
    projectString += "      <SubSystem>" + subsystem + "/SubSystem>\n";
    projectString += "      <GenerateDebugInformation>true</GenerateDebugInformation>\n";
    projectString += "      <EnableCOMDATFolding>true</EnableCOMDATFolding>\n";
    projectString += "      <OptimizeReferences>true</OptimizeReferences>\n";
    projectString += "    </Link>\n";
    projectString += "  </ItemDefinitionGroup>\n";

    // Closing
    projectString += "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\" />\n";
    projectString += "  <ImportGroup Label=\"ExtensionTargets\">\n";
    projectString += "  </ImportGroup>\n";
    projectString += "</Project>\n";


    // Now write it out
    std::ofstream outFile(project.name + ".vcxproj");
    outFile << projectString;
    outFile.close();
}
