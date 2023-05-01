//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_STACKLAYOUT_HPP
#define PICO_KIT_FRAMEWORK_STACKLAYOUT_HPP

#include "include.hpp"
#include "Layout.hpp"
#include <type_traits>

using namespace rpgui::type;
using namespace rpgui::common;

namespace rpgui::layout
{

    class StackLayout : public Layout
    {
    private:
        uint16_t _currentHeight = 0;

    public:
        StackLayout() = delete;
        StackLayout(const StackLayout &) = delete;
        ~StackLayout() = default;

        StackLayout(const Point start, const Width width, const Height height)
            : Layout(Bounds{start.x, start.y, width.v, height.v}) {}

        void Draw() const final;


        ID AddElement(VisualElement *element, const Margin &margin = Margin())
        {
            auto bounds = this->GetBounds();
            auto elementHeigth = element->GetBounds().h;
            element->SetParrent(this);

            bounds.y += _currentHeight;
            bounds.h = elementHeigth;

            auto adjusted = Bounds::GetAdjustedBounds(bounds, margin);

            element->SetBounds(adjusted);

            _currentHeight += elementHeigth;

            return AddChildren(element);
        }
    };

} // namespace rpgui::layout

#endif // PICO_KIT_FRAMEWORK_STACKLAYOUT_HPP
