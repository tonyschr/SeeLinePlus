#pragma once

#include "LineWindow.h"

class FancyLine : public LineWindow
{
public:
    std::wstring GetName() override;
    int GetLineWidth();
    int GetLineHeight();
    SIZE GetWindowSize() override;
    POINT GetWindowOffset() override;

protected:
    bool WindowFollowsMouse() override;
    void DrawLineBitmap(Graphics& graphics) override;
};