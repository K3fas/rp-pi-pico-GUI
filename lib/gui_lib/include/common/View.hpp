//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_VIEW_HPP
#define PICO_KIT_FRAMEWORK_VIEW_HPP

#include <stdint.h>
#include <vector>
#include "include.hpp"


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

        std::vector<VisualElement *> _children;
        VisualElement* _activeElement = nullptr;

    public:

        View() = default;
        View(const View &) = default;
        virtual ~View();
        View(const Bounds &coords, const Color color) : VisualElement(coords, color) {}

        const std::vector<VisualElement *> &GetChildren() const;
        ID AddChildren(VisualElement* child);

        ID SetActive(VisualElement* element);
        VisualElement* GetActive() const;
    };
} // namespace rpgui::common

#endif // PICO_KIT_FRAMEWORK_VIEW_HPP