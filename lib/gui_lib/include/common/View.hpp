//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_VIEW_HPP
#define PICO_KIT_FRAMEWORK_VIEW_HPP

#include <stdint.h>
#include "Base.hpp"

namespace rpgui::type
{
    struct Point;
    struct Margin;
}

using namespace rpgui::type;

namespace rpgui::common
{
    enum class VerticalAlignment
    {
        Top,
        Center,
        Bottom,
        Fill
    };
    enum class HorizontalAlignment
    {
        Left,
        Center,
        Right,
        Fill
    };

    class View : public VisualElement
    {
    private:

    public:

        View() = default;
        View(const View &) = default;
        View(const Bounds &coords, const Color color) : VisualElement(coords, color) {}
        virtual ~View() {}

        static const Bounds GetAdjustedBounds(const Bounds &bounds, const Margin& margin);

        bool IsInBounds(const Point &point);
        static bool IsInBounds(const Bounds bounds,const Point &point);
    };
} // namespace rpgui::common

#endif // PICO_KIT_FRAMEWORK_VIEW_HPP