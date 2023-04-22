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
        if(_parrent)
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
        IVGA::IDrawRectangle(this->_bounds,Color::Black);
        this->_bounds = bounds;
        // TODO: Test this ...
    }
} // namespace rpgui::common
