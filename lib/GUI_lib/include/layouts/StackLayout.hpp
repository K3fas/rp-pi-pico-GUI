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
        void Draw(const Bounds &coords) const final;

        template <typename T>
        bool AddElement(const T &element)
        {
            auto cp = new T(element);
            View *toAdd = cp;

            toAdd->SetParrent(this);
            auto elementHeigth = toAdd->GetBounds().h;
            auto bounds = this->GetBounds();
            bounds.y += _currentHeight;
            bounds.h = elementHeigth;

            auto adjusted = GetAdjustedBounds(bounds, toAdd->margin);

            toAdd->SetBounds(adjusted);

            _currentHeight += elementHeigth;

            _children.emplace_back(toAdd);
            return true;
        }
    };

} // namespace rpgui::layout

#endif // PICO_KIT_FRAMEWORK_STACKLAYOUT_HPP
