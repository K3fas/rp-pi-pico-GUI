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

    const Bounds View::GetAdjustedBounds(const Bounds &bounds, const Margin &margin)
    {
        return Bounds{
            bounds.x + margin.l,
            bounds.y + margin.t,
            bounds.w - margin.l - margin.r,
            bounds.h - margin.t - margin.b,
        };
    }

    const Bounds View::GetAdjustedBounds() const
    {
        return GetAdjustedBounds(this->GetBounds(), this->GetMargin());
    }
    Clickable::Clickable()
    {
    }

    Clickable::~Clickable()
    {
    }

} // namespace rpgui::common
