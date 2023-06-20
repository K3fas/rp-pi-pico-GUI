#pragma once

#include "VColors.hpp"

#include "Element.hpp"
#include "Bounds.hpp"

using namespace rpgui::colors;

namespace rpgui::common
{
    /// @brief Base class of every drawable element
    class VisualElement : public Element
    {
    protected:

        /// @brief Position and size of element on the display
        Bounds _bounds;

    public:

        /// @brief Base color of element
        Color color;

    public:
        VisualElement();
        VisualElement(const Bounds &bounds, const Color color) : _bounds(bounds), color(color) {}
        VisualElement(const VisualElement &) = default;
        virtual ~VisualElement();

        /// @brief Bounds getter
        /// @return Bounds of element
        const Bounds &GetBounds() const { return _bounds; }

        /// @brief Bounds setter
        /// @param bounds New bounds of element
        virtual void SetBounds(const Bounds &bounds);

        /// @brief Determine if point is inside bounds of element
        /// @param point Point to be determined
        /// @return True if point is inside bounds
        bool IsInBounds(const Point &point);


        /// @brief Determine if point is inside bounds of element
        /// @param bounds Bounds of element
        /// @param point Point to be determined
        /// @return True if point is inside bounds
        static bool IsInBounds(const Bounds bounds, const Point &point);

        /// @brief Pure virtual draw function
        virtual void Draw() const = 0;
    };
} // namespace rpgui::common
