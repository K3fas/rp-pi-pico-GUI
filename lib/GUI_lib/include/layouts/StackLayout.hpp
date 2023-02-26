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
    public:
        StackLayout(const rpgui::types::Point start, const rpgui::types::Width width, const rpgui::types::Height height)
            : Layout(rpgui::common::Coord{start.x, start.y, width.v, height.v}) {}
        ~StackLayout();

        void Draw() const;
    };

} // namespace rpgui::layout

#endif // PICO_KIT_FRAMEWORK_STACKLAYOUT_HPP
