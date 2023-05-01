//
// Created by kefas on 26.2.23.
//

#include "common/Base.hpp"
#include "Base.hpp"
#include "IVGA.hpp"

namespace rpgui::common
{

    Element::Element() : _id(++_count)
    {
    }

    Element::~Element()
    {
    }

    void Element::SetActive(Element *element)
    {
        if (_parrent)
            _parrent->SetActive(element);
    }

    VisualElement::VisualElement()
    {
    }

    VisualElement::~VisualElement()
    {
    }

    void VisualElement::SetBounds(const Bounds &bounds)
    {
        IVGA::IDrawRectangle(this->_bounds, Color::Black);
        this->_bounds = bounds;
    }
    bool VisualElement::IsInBounds(const Point &point)
    {
        auto bounds = this->GetBounds();
        if (point.x > bounds.x && point.x < bounds.x + bounds.w &&
            point.y > bounds.y && point.y < bounds.y + bounds.h)
            return true;

        return false;
    }
    
    bool VisualElement::IsInBounds(const Bounds bounds, const Point &point)
    {
        if (point.x > bounds.x && point.x < bounds.x + bounds.w &&
            point.y > bounds.y && point.y < bounds.y + bounds.h)
            return true;

        return false;
    }
} // namespace rpgui::common
