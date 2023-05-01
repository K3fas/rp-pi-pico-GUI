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


    public:
        Layout() = default;
        Layout(const Layout&) = delete; 
        virtual ~Layout() = default;

        Layout(const Bounds coords, Color bgColor = colors::Color::Transparent);
       
        
    };

} // namespace rpgui::layout

#endif // PICO_KIT_FRAMEWORK_AYOUT_HPP
