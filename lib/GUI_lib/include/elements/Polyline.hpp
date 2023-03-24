//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_POLYLINE_HPP
#define PICO_KIT_FRAMEWORK_POLYLINE_HPP

#include "include.hpp"
#include <vector>

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::colors;

namespace rpgui::ui
{
    class Polyline : public View
    {
    private:

    std::vector<Point> _points;
        
    public:
        Polyline() = delete;
        Polyline(const Polyline&) = default;
        ~Polyline() = default;

        Polyline(const std::vector<Point> &points, Color color);

        void AddPoint(const Point& point);

        void Draw() const final;
    };
    
    
} // namespace rpgui::ui


#endif //PICO_KIT_FRAMEWORK_POLYLINE_HPP
