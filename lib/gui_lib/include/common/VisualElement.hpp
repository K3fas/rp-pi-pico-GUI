#pragma once

#include "VColors.hpp"

#include "Element.hpp"
#include "Bounds.hpp"

using namespace rpgui::colors;

namespace rpgui::common
{
        class VisualElement : public Element
    {
    protected:
        Bounds _bounds;

    public:
        Color color;

    public:
        VisualElement();
        VisualElement(const Bounds &bounds, const Color color) : _bounds(bounds), color(color) {}
        VisualElement(const VisualElement &) = default;
        virtual ~VisualElement();

        const Bounds &GetBounds() const { return _bounds; }

        virtual void SetBounds(const Bounds &bounds);

        bool IsInBounds(const Point &point);
        static bool IsInBounds(const Bounds bounds, const Point &point);

        virtual void Draw() const = 0;
    };
} // namespace rpgui::common
