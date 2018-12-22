#include "stdafx.h"
#include "FancyLine.h"

std::wstring FancyLine::GetName()
{
    return L"Fancy line";
}

int FancyLine::GetLineWidth()
{
    // Percentage of the screen for size and resolution independence.
    return static_cast<int>(GetScreenWidth() * 0.75);
}

int FancyLine::GetLineHeight()
{
    // Percentage of the screen for size and resolution independence.
    return static_cast<int>(GetScreenHeight() * 0.05);
}

SIZE FancyLine::GetWindowSize()
{
    // The line is as wide as the screen and two pixels high.
    return SIZE { GetLineWidth(), GetLineHeight() };
}

POINT FancyLine::GetWindowOffset()
{
    return POINT { -GetLineWidth() / 2, 10 };
}

bool FancyLine::WindowFollowsMouse()
{
    return true;
}

void FancyLine::DrawLineBitmap(Graphics& graphics)
{
    graphics.Clear(Color(0, 0, 0, 0));

    // White line, with ~40% opacity.
    SolidBrush lightGreyBrush(Color(100, 255, 255, 255));
    graphics.FillRectangle(&lightGreyBrush, 0, 0, GetLineWidth(), 1);

    // Black line, with ~40% opacity.
    SolidBrush darkGreyBrush(Color(100, 0, 0, 0));
    graphics.FillRectangle(&darkGreyBrush, 0, 1, GetLineWidth(), 1);

    // Centered thicker blue line.
    SolidBrush blueBrush(Color(200, 0, 0, 200));
    int centeredLineWith = GetLineWidth() / 2;
    graphics.FillRectangle(&blueBrush, centeredLineWith / 2, 2, centeredLineWith, 5);

    // Centered vertical thin green gradient line.
    Point topCenter(GetLineWidth() / 2, 4);
    Point bottomCenter(GetLineWidth() / 2, GetLineHeight());
    LinearGradientBrush greenGradient(topCenter, bottomCenter, Color(254, 0, 200, 0), Color(0, 0, 200, 0));
    graphics.FillRectangle(&greenGradient, GetLineWidth() / 2 - 1, 2, 2, GetLineHeight());
}
