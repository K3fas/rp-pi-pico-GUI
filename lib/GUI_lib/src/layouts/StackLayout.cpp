//
// Created by kefas on 26.2.23.
//

#include "../../include/layouts/StackLayout.hpp"
#include "../../include/include.hpp"

namespace rpgui::layout
{

    StackLayout::~StackLayout()
    {
    }

    void StackLayout::Draw() const
    {
        for (auto &&element : _children)
        {
            element->Draw();
        }
    }

} // namespace rpgui::layout