#pragma once
#include <windows.h>
#include <stdio.h>
#include <string.h>

//Print if debugging ... learned that from meterpreter source code, metasploit.
#ifndef _DEBUG
#define dprintf(...) do{}while(0); //if debug not defined, it will do nothing.
#else
#define dprintf(...) wprintf_s(__VA_ARGS__) //if debug enabled, it will printf everything. 
#endif

// Function prototypes goes here
LONGLONG SizeFromName(LPCWSTR szFileName);									// Provide a filename, it returns the filesize in bytes.
int CopyFileToBuffer(LPCWSTR szFileName, char* buffer);						// Copies file contents to buffer
int PatchString(char* buffer, char* cOriginal, char* cReplacement);			// Search and replace a string in a given buffer.
