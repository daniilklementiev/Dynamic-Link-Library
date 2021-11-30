// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <sstream>

#define DLLEXPORT __declspec(dllexport)

extern "C"
{
    DLLEXPORT long Sqr(long x) { return x * x; }
    DLLEXPORT long Cube(long x) { return x * x * x; }
    DLLEXPORT int hex2dec(char* hex) {

        std::stringstream stream;

        int dec;
        stream << hex;
        stream >> std::hex >> dec;

        return dec;
    }

    DLLEXPORT char* dec2hex(int dec) {

        char* hex = new char[100];
        _itoa_s(dec, hex, 99, 16);

        return hex;
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

