//
// Created by kefas on 26.2.23.
//

#include "Element.hpp"
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


} // namespace rpgui::common
