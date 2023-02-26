//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_AYOUT_HPP
#define PICO_KIT_FRAMEWORK_AYOUT_HPP

#include <vector>
#include <type_traits>
#include "../include.hpp"

using namespace rpgui::common;
using namespace rpgui::types;

namespace rpgui::layout
{
    class Layout : public View
    {
    private:
        std::vector<View *> _children;

    public:
        Layout() = delete;
        Layout(const Coord coords, Color bgColor = colors::Color::Black) : View(coords, bgColor) {}

        ~Layout()
        {
            for (auto &&element : _children)
            {
                delete element;
            }
        }

        const std::vector<View *> &GetChildren() const
        {
            return _children;
        }

        bool AddElement(View *element)
        {
            if (!element)
                return false;

            _children.emplace_back(element);
            return true;
        }
    };

} // namespace rpgui::layout

#endif // PICO_KIT_FRAMEWORK_AYOUT_HPP
