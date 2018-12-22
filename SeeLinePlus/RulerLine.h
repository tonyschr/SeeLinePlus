#pragma once

#pragma once

#include "LineWindow.h"

class RulerLine : public LineWindow
{
public:
    std::wstring GetName() override;
    SIZE GetWindowSize() override;

protected:
    bool WindowFollowsMouse() override;
    void DrawLineBitmap(Graphics& graphics) override;

private:
    int GetWidth();
    int GetHeight();
};