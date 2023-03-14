//
// Created by kefas on 26.2.23.
//

#include "common/Base.hpp"

namespace rpgui::common
{

    Element::Element() : _id(_count++)
    {
    }

    Element::~Element()
    {
    }

    VisualElement::VisualElement()
    {
    }

    VisualElement::~VisualElement()
    {
    }

    void VisualElement::SetBounds(const Bounds &bounds)
    {
        this->_bounds = bounds;
    }

} // namespace rpgui::common
