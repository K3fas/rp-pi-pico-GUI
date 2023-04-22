//
// Created by kefas on 26.2.23.
//

#include "common/View.hpp"
#include "common/Base.hpp"
#include "common/Types.hpp"
#include "View.hpp"

using namespace rpgui::common;

const Bounds View::GetAdjustedBounds(const Bounds &bounds, const Margin &margin)
{
    return Bounds(
        bounds.x + margin.l,
        bounds.y + margin.t,
        bounds.w - margin.l - margin.r,
        bounds.h - margin.t - margin.b);
}

const Bounds View::GetAdjustedBounds() const
{

    return GetAdjustedBounds(this->GetBounds(), this->margin);
}

bool rpgui::common::View::IsInBounds(const rpgui::type::Point& point)
{
    auto bounds = this->GetBounds();
    if (point.x > bounds.x && point.x < bounds.x + bounds.w &&
        point.y > bounds.y && point.y < bounds.y + bounds.h)
        return true;

    
    return false;
}

bool rpgui::common::View::IsInBounds(const rpgui::common::Bounds bounds, const rpgui::type::Point &point)
{
    if (point.x > bounds.x && point.x < bounds.x + bounds.w &&
        point.y > bounds.y && point.y < bounds.y + bounds.h)
        return true;

    
    return false;
}
