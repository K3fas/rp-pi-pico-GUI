//
// Created by kefas on 26.2.23.
//

#include "StackLayout.hpp"
#include "include.hpp"
#include "IVGA.hpp"

namespace rpgui::layout
{

    StackLayout::~StackLayout()
    {
    }

    void StackLayout::Draw() const
    {
        if(color != Color::Transparent)
        {
            IVGA::IDrawRectangle(GetBounds(),color);
        }
        for (auto &&element : _children)
        {
            element->Draw();
        }
    }

} // namespace rpgui::layout