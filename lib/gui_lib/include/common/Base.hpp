//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_BASE_HPP
#define PICO_KIT_FRAMEWORK_BASE_HPP

#include "Types.hpp"
#include "Bounds.hpp"
#include "VColors.hpp"

using namespace rpgui::colors;
using namespace rpgui::type;

namespace rpgui::common
{
    class Clickable;
    using EventHandler = void (*)(Clickable &sender);

    class Element
    {
    private:
        inline static uint16_t _count = 0;
        rpgui::type::ID _id;
        Element *_parrent;

    public:
        Element();
        Element(const Element &) = default;
        virtual ~Element();

        void SetParrent(Element *parrent) { _parrent = parrent; }

        /// @brief Callback function for setting ellement as active on screen
        /// @param element
        virtual void SetActive(Element *element);

        const Element *GetParrent() const { return _parrent; }
        const uint16_t GetId() const { return _id; }
        static uint16_t GetElementCount() { return _count; }
    };

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

#endif // PICO_KIT_FRAMEWORK_BASE_HPP
