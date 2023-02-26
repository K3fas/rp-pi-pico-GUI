//
// Created by kefas on 26.2.23.
//

#include "../../include/layouts/StackLayout.hpp"
#include "../../include/include.hpp"

namespace rpgui::layout
{

    StackLayout::~StackLayout()
    {
    }

    void StackLayout::Draw() const
    {
        auto coord = this->GetCoords();
        auto elements = this->GetChildren();

        // TODO HANDLE MARGINS
        for (auto &&element : elements)
        {
            auto elCoord = element->GetCoords();
            coord.h = elCoord.h; // sets heiht of item and draws it
            element->SetCoords(coord);
            element->Draw();

            coord.y += elCoord.h; // prepares start point for next element
        }
    }

} // namespace rpgui::layout