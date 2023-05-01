#include "VisualElement.hpp"

#include "Bounds.hpp"
#include "IVGA.hpp"

using namespace rpgui::colors;

rpgui::common::VisualElement::VisualElement()
{
}

rpgui::common::VisualElement::~VisualElement()
{
}

void rpgui::common::VisualElement::SetBounds(const Bounds &bounds)
{
    IVGA::IDrawRectangle(this->_bounds, Color::Black);
    this->_bounds = bounds;
}
bool rpgui::common::VisualElement::IsInBounds(const Point &point)
{
    auto bounds = this->GetBounds();
    if (point.x > bounds.x && point.x < bounds.x + bounds.w &&
        point.y > bounds.y && point.y < bounds.y + bounds.h)
        return true;

    return false;
}

bool rpgui::common::VisualElement::IsInBounds(const Bounds bounds, const Point &point)
{
    if (point.x > bounds.x && point.x < bounds.x + bounds.w &&
        point.y > bounds.y && point.y < bounds.y + bounds.h)
        return true;

    return false;
}