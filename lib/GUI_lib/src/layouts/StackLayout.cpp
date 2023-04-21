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
        for (auto &&element : _children)
        {
            element->Draw();
        }
        if (_activeElement)
        {
            auto element = (VisualElement *)_activeElement;
            element->Draw();
        }
    }

    void StackLayout::SetActive(Element *element)
    {
        _activeElement = element;
    }

} // namespace rpgui::layout