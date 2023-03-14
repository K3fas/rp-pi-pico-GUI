//
// Created by kefas on 26.2.23.
//
#include "Button.hpp"
#include "rp_core.hpp"
#include "IVGA.hpp"

void rpgui::ui::Button::Draw() const
{
    IVGA::IDrawRectangle(this->GetBounds(), this->color);
}

