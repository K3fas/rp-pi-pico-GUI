//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_RECTANGLE_HPP
#define PICO_KIT_FRAMEWORK_RECTANGLE_HPP

#include "include.hpp"

using namespace rpgui::type;
using namespace rpgui::common;

namespace rpgui::ui
{
    class Rectangle : public common::View
    {
    private:
    public:
        Rectangle(const rpgui::type::Width width, const rpgui::type::Height height, const Color color)
            : View(rpgui::common::Bounds{0, 0, width.v, height.v}, color) {}
        Rectangle(const Bounds &bounds, const Color color)
            : View(bounds, color) {}

        ~Rectangle() {}

        void Draw() const final;
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_RECTANGLE_HPP
