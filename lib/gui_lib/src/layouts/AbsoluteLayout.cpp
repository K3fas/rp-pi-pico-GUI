//
// Created by kefas on 26.2.23.
//

#include "AbsoluteLayout.hpp"
#include "IVGA.hpp"

void rpgui::layout::AbsoluteLayout::SetActive(Element *element)
{
    _activeElement = element;
}

void rpgui::layout::AbsoluteLayout::Draw() const
{
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
