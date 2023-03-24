//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_AYOUT_HPP
#define PICO_KIT_FRAMEWORK_AYOUT_HPP

#include <vector>
#include <type_traits>
#include "include.hpp"

using namespace rpgui::common;
using namespace rpgui::type;

namespace rpgui::layout
{
    class Layout : public View
    {
    protected:
        std::vector<View *> _children;
        Element* _activeElement = nullptr;

    public:
        Layout() = delete;
        Layout(const Layout&) = delete; 
        ~Layout();

        Layout(const Bounds coords, Color bgColor = colors::Color::Transparent);
       
        const std::vector<View *> &GetChildren() const;
    };

} // namespace rpgui::layout

#endif // PICO_KIT_FRAMEWORK_AYOUT_HPP
