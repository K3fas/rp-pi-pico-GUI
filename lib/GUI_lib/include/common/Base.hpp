//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_BASE_HPP
#define PICO_KIT_FRAMEWORK_BASE_HPP

#include "stdint.h"
#include "../../include/VColors.hpp"

using namespace rpgui::colors;

namespace rpgui::common
{
    class Clickable;
    using EventHandler = void (*)(Clickable &sender);

    struct Coord
    {
        int16_t x, y;
        uint16_t w, h;

        Coord() : x(0), y(0), w(0), h(0) {}
        Coord(int16_t x, int16_t y, uint16_t w, uint32_t h)
            : x(x), y(y), w(w), h(h) {}
    };

    struct Margin
    {
        uint8_t l, t, r, b;

        Margin() : l(0), t(0), r(0), b(0) {}
        Margin(uint8_t l, uint8_t t, uint8_t r, uint8_t b)
            : l(l), t(t), r(r), b(b) {}
    };

    class Element
    {
    private:
        inline static uint16_t _count = 0;
        uint16_t _id;
        Element *_parrent;

    public:
        Element();
        virtual ~Element();
    };

    class VisualElement : public Element
    {
    private:
        Coord _coords;

    public:
        Color color;

    public:
        VisualElement();
        VisualElement(const Coord &coords, const Color color) : _coords(coords), color(color) {}

        virtual ~VisualElement();

        const Coord &GetCoords() const { return _coords; }

        void SetCoords(const Coord &coords);
        virtual void Draw() const = 0;
    };

    class View : public VisualElement
    {
    private:
        Margin _margin;

    public:
        View();
        View(const Coord &coords, const Color color) : VisualElement(coords, color) {}
        virtual ~View();
    };

    class Clickable
    {
    private:
        EventHandler _clicked, _pressed, _released;

    public:
        Clickable();
        ~Clickable();
    };

} // namespace rpgui::common

#endif // PICO_KIT_FRAMEWORK_BASE_HPP
