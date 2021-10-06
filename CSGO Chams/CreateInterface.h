#pragma once
#include <Windows.h>

typedef void* (__cdecl* tCreateInterface)(const char* name, int* returnCode);

void* GetInterface(const char* dllname, const char* interfacename)
{
	tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandle(dllname), "CreateInterface");

	int returnCode = 0;
	void* iinterface = CreateInterface(interfacename, &returnCode);

	return iinterface;
}
