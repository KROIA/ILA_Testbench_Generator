#pragma once
#include "ILA_Testbench_Generator_global.h"

/// USER_SECTION_START 1

/// USER_SECTION_END

// Debugging
#ifdef NDEBUG
	#define ILATG_CONSOLE(msg)
	#define ILATG_CONSOLE_FUNCTION(msg)
#else
	#include <iostream>

	#define ILATG_DEBUG
	#define ILATG_CONSOLE_STREAM std::cout

	#define ILATG_CONSOLE(msg) ILATG_CONSOLE_STREAM << msg;
	#define ILATG_CONSOLE_FUNCTION(msg) ILATG_CONSOLE_STREAM << __PRETTY_FUNCTION__ << " " << msg;
#endif

/// USER_SECTION_START 2

/// USER_SECTION_END

#ifdef ILATG_PROFILING
	#include "easy/profiler.h"
	#include <easy/arbitrary_value.h> // EASY_VALUE, EASY_ARRAY are defined here

	#define ILATG_PROFILING_BLOCK_C(text, color) EASY_BLOCK(text, color)
	#define ILATG_PROFILING_NONSCOPED_BLOCK_C(text, color) EASY_NONSCOPED_BLOCK(text, color)
	#define ILATG_PROFILING_END_BLOCK EASY_END_BLOCK
	#define ILATG_PROFILING_FUNCTION_C(color) EASY_FUNCTION(color)
	#define ILATG_PROFILING_BLOCK(text, colorStage) ILATG_PROFILING_BLOCK_C(text,profiler::colors::  colorStage)
	#define ILATG_PROFILING_NONSCOPED_BLOCK(text, colorStage) ILATG_PROFILING_NONSCOPED_BLOCK_C(text,profiler::colors::  colorStage)
	#define ILATG_PROFILING_FUNCTION(colorStage) ILATG_PROFILING_FUNCTION_C(profiler::colors:: colorStage)
	#define ILATG_PROFILING_THREAD(name) EASY_THREAD(name)

	#define ILATG_PROFILING_VALUE(name, value) EASY_VALUE(name, value)
	#define ILATG_PROFILING_TEXT(name, value) EASY_TEXT(name, value)

#else
	#define ILATG_PROFILING_BLOCK_C(text, color)
	#define ILATG_PROFILING_NONSCOPED_BLOCK_C(text, color)
	#define ILATG_PROFILING_END_BLOCK
	#define ILATG_PROFILING_FUNCTION_C(color)
	#define ILATG_PROFILING_BLOCK(text, colorStage)
	#define ILATG_PROFILING_NONSCOPED_BLOCK(text, colorStage)
	#define ILATG_PROFILING_FUNCTION(colorStage)
	#define ILATG_PROFILING_THREAD(name)

	#define ILATG_PROFILING_VALUE(name, value)
	#define ILATG_PROFILING_TEXT(name, value)
#endif

// Special expantion tecniques are required to combine the color name
#define CONCAT_SYMBOLS_IMPL(x, y) x##y
#define CONCAT_SYMBOLS(x, y) CONCAT_SYMBOLS_IMPL(x, y)



// Different color stages
#define ILATG_COLOR_STAGE_1 50
#define ILATG_COLOR_STAGE_2 100
#define ILATG_COLOR_STAGE_3 200
#define ILATG_COLOR_STAGE_4 300
#define ILATG_COLOR_STAGE_5 400
#define ILATG_COLOR_STAGE_6 500
#define ILATG_COLOR_STAGE_7 600
#define ILATG_COLOR_STAGE_8 700
#define ILATG_COLOR_STAGE_9 800
#define ILATG_COLOR_STAGE_10 900
#define ILATG_COLOR_STAGE_11 A100 
#define ILATG_COLOR_STAGE_12 A200 
#define ILATG_COLOR_STAGE_13 A400 
#define ILATG_COLOR_STAGE_14 A700 

namespace ILA_Testbench_Generator
{
	class ILA_TESTBENCH_GENERATOR_EXPORT Profiler
	{
	public:
		// Implementation defined in LibraryName_info.cpp to save files.
		static void start();
		static void stop();
		static void stop(const char* profilerOutputFile);
	};
}


// General
#define ILATG_GENERAL_PROFILING_COLORBASE Cyan
#define ILATG_GENERAL_PROFILING_BLOCK_C(text, color) ILATG_PROFILING_BLOCK_C(text, color)
#define ILATG_GENERAL_PROFILING_NONSCOPED_BLOCK_C(text, color) ILATG_PROFILING_NONSCOPED_BLOCK_C(text, color)
#define ILATG_GENERAL_PROFILING_END_BLOCK ILATG_PROFILING_END_BLOCK;
#define ILATG_GENERAL_PROFILING_FUNCTION_C(color) ILATG_PROFILING_FUNCTION_C(color)
#define ILATG_GENERAL_PROFILING_BLOCK(text, colorStage) ILATG_PROFILING_BLOCK(text, CONCAT_SYMBOLS(ILATG_GENERAL_PROFILING_COLORBASE, colorStage))
#define ILATG_GENERAL_PROFILING_NONSCOPED_BLOCK(text, colorStage) ILATG_PROFILING_NONSCOPED_BLOCK(text, CONCAT_SYMBOLS(ILATG_GENERAL_PROFILING_COLORBASE, colorStage))
#define ILATG_GENERAL_PROFILING_FUNCTION(colorStage) ILATG_PROFILING_FUNCTION(CONCAT_SYMBOLS(ILATG_GENERAL_PROFILING_COLORBASE, colorStage))
#define ILATG_GENERAL_PROFILING_VALUE(name, value) ILATG_PROFILING_VALUE(name, value)
#define ILATG_GENERAL_PROFILING_TEXT(name, value) ILATG_PROFILING_TEXT(name, value)


/// USER_SECTION_START 3

/// USER_SECTION_END