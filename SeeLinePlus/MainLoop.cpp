#include "stdafx.h"
#include "RulerLine.h"
#include "ClassicLine.h"

using namespace Gdiplus;

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

    //LineWindow* line = new RulerLine();
    LineWindow* line = new ClassicLine();
    line->Initialize();

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);

    return 0;
}

