#include "stdafx.h"
#pragma comment(lib,"gdiplus.lib")

// Global handle to our module for convenience.
HINSTANCE g_instance = NULL;

int GetScreenWidth()
{
    return GetSystemMetrics(SM_CXSCREEN);
}

int GetScreenHeight()
{
    return GetSystemMetrics(SM_CYSCREEN);
}
