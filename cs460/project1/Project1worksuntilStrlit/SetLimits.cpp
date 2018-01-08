//File: SetLimits.cpp
//Author: Mahesh Gautam
//Class: CS 460
//Instructor: Dr. Tia Watts
//Date/Semester: Spring 2016
//Assignment: Project 1 aka Lexical Analyzer
//Description: This program reads in a source file (.in or .py) and produces a listing file (.lst) and
//a debugging (.dbg) file. The listing file contains the lines of input file with line numbers and errors.
//The debugging file contains the lines of input file with line numbers, errors, and following each line,
//a list of the lexemes found on the line and their corresponding tokens. This analyzer recognizes lexemes 
//for identifiers, numeric literals and symbols that were given in a hand-out. 

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include "SetLimits.h"

void SetLimits ()
{
	// Beginning of resource limit code
	int getrlimit(int resource, struct rlimit *rlim);
	int getrusage(int who, struct rusage *usage);
	int setrlimit(int resource, const struct rlimit *rlim);
	struct rlimit __trl1;
	const int __trl1r = getrlimit(RLIMIT_CPU, & __trl1);
	struct rlimit __trl2 = {20, __trl1.rlim_max};
	const int __trl2r = setrlimit(RLIMIT_CPU, & __trl2);
	struct rlimit __trl3;
	const int __trl3r = getrlimit(RLIMIT_FSIZE, & __trl3);
	struct rlimit __trl4 = {10000000, __trl3.rlim_max};
	const int __trl4r = setrlimit(RLIMIT_FSIZE, & __trl4);
	// End of time limit code
}
