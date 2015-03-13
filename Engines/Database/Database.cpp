// Syntax Database.cpp : Defines the entry point for the DLL application.
//
#include "Database.h"
#include "DatabaseImpl.h"

using namespace std;
using namespace CR;
using namespace CR::Database;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

#ifdef _WINDOWS
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}
#endif

#ifdef WINCE
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}
#endif

#ifdef _MANAGED
#pragma managed(pop)
#endif


IDatabase* DatabaseFactory::CreateDatabase(const std::wstring& fileName)
{
	return new DatabaseImpl(fileName);
}