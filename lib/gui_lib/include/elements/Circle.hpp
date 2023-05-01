#pragma once

#include "include.hpp"

using namespace rpgui::common;
using namespace rpgui::type;

namespace rpgui::ui
{
    class Circle : public VisualElement
    {
    private:

        Point center;
    public:
        Radius radius;

        Circle() = delete;
        Circle(const Circle&) = delete;
        ~Circle() = default;

        Circle(const Radius& radius, Color color);

        void Draw() const final;

        void SetCenter(const Point& center);
        const Point& GetCenter();

    };
    
    
    
} // namespace rpgui::ui
