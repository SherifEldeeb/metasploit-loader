#include "main.h"
DWORD err = 0;

LONGLONG SizeFromName(LPCWSTR szFileName) // Returns a file's size from its filename, returns a LONGLONG, in case you have a LARGE LARGE file :)
{
	LARGE_INTEGER fileSize = {0};
	HANDLE hfile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //Get a handle on the file
	
	if (hfile==INVALID_HANDLE_VALUE) //if something went wrong ...
	{
		err = GetLastError();
		dprintf(L"[-] Invalid file handle! CreateFile() returned : %08x\n", err);
		return -1;
	}

	if(!GetFileSizeEx(hfile,&fileSize)) // Get the size from the file handle
	{
		err = GetLastError();
		dprintf(L"[-] Error getting file size! GetFileSizeEx() returned : %08x\n", err);
		return -1;
	}

#ifndef _DEBUG
	CloseHandle(hFile); // this will ALWAYS throw an exception if run under a debugger, but good higene if run under "production"
#endif 
	return fileSize.QuadPart; //LARGE_INTEGER is a sruct, QuadPart is the filesize in a 64bit digit... which should cover all file sizes "That's for files >4GB" 
} 

int CopyFileToBuffer(LPCWSTR szFileName, char* buffer)
{
	dprintf(L"[*] Copying file \"%s\" to buffer...\n", szFileName);
	LONGLONG size = 0;
	size = SizeFromName(szFileName);
	if (size == -1)
	{
		return -1;
	}
	else {
		dprintf(L"[*] Size of \"%s\" is \"%d\" bytes.\n", szFileName, size);
	}

	dprintf(L"[*] Trying to VirtualAlloc \"%d + 5\" bytes of data ... the extra 5 are for ASM voodoo\n", size);
	buffer = (char*)VirtualAlloc(0, (SIZE_T)size + 5, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (buffer == NULL)
	{
		err = GetLastError();
		dprintf(L"[-] Failed to allocate memory! VirtualAlloc() returned : %08x\n", err);
		return -1;
	}
	dprintf(L"[*] Success! \"%d + 5\" bytes of data allocated.\n", size);
	return 0;
}

int PatchString(char* buffer, char* cOriginal, char* cReplacement)
{
	char* pOffset = nullptr;
	//dprintf(L"[*] Patching buffer: \"%s\" -> \"%s\"...\n", (wchar_t)cOriginal, (wchar_t)cReplacement);
	//pOffset = strstr(buffer, cOriginal); //strstr doesn't work on binary data ... :/
	if (pOffset == NULL || pOffset == nullptr)
	{
	dprintf(L"[-] Couldn't get the offset of \"%s\" ... it's either not there, or something screwed up.", cOriginal);
	return 1;
	}
	else {
			dprintf(L"[*] Found \"%s\" at offset \"0x%08x\".", cOriginal, pOffset);
	}

	return 0;
}

