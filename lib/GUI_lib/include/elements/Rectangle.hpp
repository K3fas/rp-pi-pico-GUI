//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_RECTANGLE_HPP
#define PICO_KIT_FRAMEWORK_RECTANGLE_HPP

#include "../include.hpp"

using namespace rpgui::types;

namespace rpgui::ui
{
    class Rectangle : public common::View
    {
    private:
    public:
        Rectangle() = delete;
        Rectangle(const Point start, const Point end, const Color color);
        Rectangle(const Point start, const Width width, const Height height, const Color color);
        ~Rectangle();

        void Draw() const final;
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_RECTANGLE_HPP
