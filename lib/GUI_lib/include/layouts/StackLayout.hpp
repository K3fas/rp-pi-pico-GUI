//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_STACKLAYOUT_HPP
#define PICO_KIT_FRAMEWORK_STACKLAYOUT_HPP

#include "../include.hpp"
#include "Layout.hpp"

namespace rpgui::layout
{

    class StackLayout : public Layout
    {
    private:
        uint16_t _currentHeight = 0;

    public:
        StackLayout(const rpgui::type::Point start, const rpgui::type::Width width, const rpgui::type::Height height)
            : Layout(rpgui::common::Bounds{start.x, start.y, width.v, height.v}) {}
        ~StackLayout();

        void Draw() const final;

        template <typename T>
        bool AddElement(T *element)
        {
            auto bounds = this->GetBounds();
            auto elementHeigth = element->GetBounds().h;
            element->SetParrent(this);
            
            bounds.y += _currentHeight;
            bounds.h = elementHeigth;

            auto adjusted = GetAdjustedBounds(bounds, element->margin);

            element->SetBounds(adjusted);

            _currentHeight += elementHeigth;

            _children.emplace_back(element);
            return true;
        }
    };

} // namespace rpgui::layout

#endif // PICO_KIT_FRAMEWORK_STACKLAYOUT_HPP
