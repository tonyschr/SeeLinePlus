#pragma once

#include "LineWindow.h"

class ClassicLine : public LineWindow
{
public:
    std::wstring GetName() override;
    SIZE GetWindowSize() override;
    POINT GetWindowOffset() override;

protected:
    bool WindowFollowsMouse() override;
    void DrawLineBitmap(Graphics& graphics) override;
};