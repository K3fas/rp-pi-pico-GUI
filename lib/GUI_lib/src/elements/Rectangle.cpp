//
// Created by kefas on 26.2.23.
//
#include "elements/Rectangle.hpp"

#include "IVGA.hpp"

void rpgui::ui::Rectangle::Draw() const
{
     IVGA::IDrawRectangle(this->GetBounds(), this->color); 
}
void rpgui::ui::Rectangle::Draw(const Bounds &bounds) const
{
     IVGA::IDrawRectangle(bounds, this->color); 
}
