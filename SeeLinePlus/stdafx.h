#pragma once

#include "targetver.h"

// Windows header files
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <windowsx.h>
#include <objidl.h>
#include <gdiplus.h>
#include <shellapi.h>
#include <strsafe.h>

// Standard C++ header files
#include <string>
#include <memory>
#include <vector>
#include <assert.h>

// Module handle
extern HINSTANCE g_instance;

#define RECTWIDTH(rc) (rc.right - rc.left)
#define RECTHEIGHT(rc) (rc.bottom - rc.top)

int GetScreenWidth();
int GetScreenHeight();
