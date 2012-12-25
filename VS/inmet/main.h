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
LONGLONG SizeFromName(LPCWSTR szFileName);												// Provide a filename, it returns the filesize in bytes.
DWORD CopyFileToBuffer(LPCWSTR szFileName, BYTE** buffer);								// Copies file contents to buffer, return buffer size.
int PatchString(BYTE* buffer, const char* cOriginal, const int index, const int NoOfBytes);		// Search and replace a string in a given buffer.
bool AnsiToUnicode(const char* ascii, wchar_t* unicode);								// Sorry for the insist on unicode support, I'm from Egypt :)
DWORD binstrstr (BYTE * buff1, int lenbuff1, BYTE * buff2, int lenbuff2);				// Binary search, return offset, or 0 if not found/error...