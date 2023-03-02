//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_VIEW_HPP
#define PICO_KIT_FRAMEWORK_VIEW_HPP

#include <stdint.h>
#include "Base.hpp"

namespace rpgui::common
{
    struct Margin
    {
        uint8_t l, t, r, b;

        Margin() : l(0), t(0), r(0), b(0) {}
        Margin(uint8_t l, uint8_t t, uint8_t r, uint8_t b)
            : l(l), t(t), r(r), b(b) {}
    };

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
        bool _bMargin;

    public:
        Margin margin;

        View() = default;
        View(const View &) = default;
        View(const Bounds &coords, const Color color) : VisualElement(coords, color) {}
        virtual ~View() {}

        static const Bounds GetAdjustedBounds(const Bounds &bounds, const Margin &margin);
        const Bounds GetAdjustedBounds() const;
    };
} // namespace rpgui::common

#endif // PICO_KIT_FRAMEWORK_VIEW_HPP