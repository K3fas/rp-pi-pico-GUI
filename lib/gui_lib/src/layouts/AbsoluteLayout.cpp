//
// Created by kefas on 26.2.23.
//

#include "AbsoluteLayout.hpp"
#include "IVGA.hpp"


void rpgui::layout::AbsoluteLayout::Draw() const
{
    for (auto &&element : GetChildren())
    {
        element->Draw();
    }
    if (GetActive())
    {
        GetActive()->Draw();
    }
}
