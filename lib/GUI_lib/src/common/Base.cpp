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

    void VisualElement::SetCoords(const Coord &coords)
    {
        this->_coords = coords;
    }

    View::View()
    {
    }

    View::~View()
    {
    }

    Clickable::Clickable()
    {
    }

    Clickable::~Clickable()
    {
    }

} // namespace rpgui::common
