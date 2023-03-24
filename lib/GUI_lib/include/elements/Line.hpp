//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_LINE_HPP
#define PICO_KIT_FRAMEWORK_LINE_HPP

#include "include.hpp"

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::colors;

namespace rpgui::ui
{
    class Line : public View
    {
    public:
        Point start,end;
        
    public:
        Line() = delete;
        Line(const Line&) = default;
        ~Line() = default;

        Line(const Point& start, const Point& end, Color color);

        void Draw() const final;
    };
    
    
} // namespace rpgui::ui


#endif //PICO_KIT_FRAMEWORK_LINE_HPP
