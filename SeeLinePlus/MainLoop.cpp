#include "stdafx.h"
#include "SeeLineTray.h"

using namespace Gdiplus;

void PumpMessages()
{
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) 
{
    g_instance = hInstance;

    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput = {};
    ULONG_PTR gdiplusToken = 0;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    SeeLineTray tray;
    if (tray.Create())
    {
        PumpMessages();
    }

    GdiplusShutdown(gdiplusToken);

    return 0;
}

