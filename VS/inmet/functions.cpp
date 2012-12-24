#include "main.h"

LONGLONG SizeFromName(LPCWSTR szFileName) // Returns a file's size from its filename, returns a LONGLONG, in case you have a LARGE LARGE file :)
{

	HANDLE hfile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //Get a handle on the file
	if (hfile==INVALID_HANDLE_VALUE) //if something went wrong ...
	{
		dprintf(L"[-] Invalid file handle! It either doesn't exist or is locked.\n", szFileName);
		return -1;
	}
	LARGE_INTEGER fileSize = {0};
	if(!GetFileSizeEx(hfile,&fileSize)) // Get the size from the file handle
	{
		dprintf(L"[-] Error getting file size from filename: %s\n", szFileName);
		return -1;
	}

#ifndef _DEBUG
	CloseHandle(hFile); // this will ALWAYS throw an exception if run under a debugger, but good higene if run under "production"
#endif 
	return fileSize.QuadPart; //LARGE_INTEGER is a sruct, QuadPart is the filesize in a 64bit digit... which should cover all file sizes "That's for files >4GB" 
} 
