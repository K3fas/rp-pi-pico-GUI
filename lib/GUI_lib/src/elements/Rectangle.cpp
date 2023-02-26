//
// Created by kefas on 26.2.23.
//

#include "../../include/elements/Rectangle.hpp"
#include "../../include/IVGA.hpp"

using namespace IVGA;
using namespace rpgui::colors;

namespace rpgui::ui
{
    Rectangle::Rectangle(const rpgui::types::Point start, const rpgui::types::Point end, const Color color)
        : View(rpgui::common::Coord{start.x, start.y, end.x - start.x, end.y - start.y}, color)
    {
    }

    Rectangle::Rectangle(const rpgui::types::Point start, const rpgui::types::Width width, const rpgui::types::Height height, const Color color)
        : View(rpgui::common::Coord{start.x, start.y, width.v, height.v}, color)
    {
    }

    Rectangle::~Rectangle()
    {
    }

    void Rectangle::Draw() const
    {
        IDrawRectangle(this->GetCoords(), this->color);
    }

} // namespace rpgui::ui