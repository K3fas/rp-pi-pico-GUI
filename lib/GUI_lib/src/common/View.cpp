//
// Created by kefas on 26.2.23.
//

#include "common/View.hpp"
#include "common/Base.hpp"

using namespace rpgui::common;

const Bounds View::GetAdjustedBounds(const Bounds &bounds, const Margin &margin)
{
    return Bounds{
        bounds.x + margin.l,
        bounds.y + margin.t,
        bounds.w - margin.l - margin.r,
        bounds.h - margin.t - margin.b,
    };
}

const Bounds View::GetAdjustedBounds() const
{
    return GetAdjustedBounds(this->GetBounds(), this->margin);
}