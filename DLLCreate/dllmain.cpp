// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#define DLLEXPORT __declspec(dllexport)

extern "C"
{
    DLLEXPORT long Sqr(long x) { return x * x; }
    DLLEXPORT long Cube(long x) { return x * x * x; }
    DLLEXPORT long Hex(WCHAR str) { 
        return Hex(str); 
    }
}
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

