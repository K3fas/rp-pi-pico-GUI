//
// Created by kefas on 26.2.23.
//

#include "../../include/common/Base.hpp"

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

    void VisualElement::SetBounds(const Bounds &coords)
    {
        this->_coords = coords;
    }

    Clickable::Clickable()
    {
    }

    Clickable::~Clickable()
    {
    }

} // namespace rpgui::common
