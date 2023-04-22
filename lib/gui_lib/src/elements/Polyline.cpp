//
// Created by kefas on 26.2.23.
//

#include "Polyline.hpp"
#include "IVGA.hpp"

rpgui::ui::Polyline::Polyline(const std::vector<Point> &points, Color color)
    :View(Bounds(),color)
{
}

void rpgui::ui::Polyline::AddPoint(const Point &point)
{
    _points.push_back(point);
}

void rpgui::ui::Polyline::Draw() const
{
    if(_points.size() < 2)
        return;
    
    for(auto it = _points.begin(); it < _points.end()-1; ++it)
    {
        IVGA::IDrawLine(*it,*(it+1),color);
    }
    
}
