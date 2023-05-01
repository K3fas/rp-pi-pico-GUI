//
// Created by kefas on 26.2.23.
//

#include "StackLayout.hpp"
#include "include.hpp"
#include "IVGA.hpp"

namespace rpgui::layout
{

    void StackLayout::Draw() const
    {
        if (color != Color::Transparent)
        {
            IVGA::IDrawRectangle(GetBounds(), color);
        }
        for (auto &&element : GetChildren())
        {
            element->Draw();
        }
        if (GetActive())
        {
            GetActive()->Draw();
        }
    }

} // namespace rpgui::layout