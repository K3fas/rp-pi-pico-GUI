//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_ABSOLUTELAYOUT_HPP
#define PICO_KIT_FRAMEWORK_ABSOLUTELAYOUT_HPP

#include "include.hpp"
#include "Layout.hpp"
#include <type_traits>

using namespace rpgui::type;
using namespace rpgui::common;

namespace rpgui::layout
{
    class AbsoluteLayout : public Layout
    {
    private:
    public:
        AbsoluteLayout() = default;
        AbsoluteLayout(const AbsoluteLayout &) = delete;
        ~AbsoluteLayout() = default; 

        void Draw() const final;

        template <typename T>
            requires std::is_base_of<VisualElement, T>::value
        ID AddElement(const Point &position, T *element)
        {
            element->SetParrent(this);

            auto bounds = element->GetBounds();
            bounds.x = position.x;
            bounds.y = position.y;
            element->SetBounds(bounds);

            return AddChildren(element);
        }
    };

} // namespace rpgui::layout;

#endif // PICO_KIT_FRAMEWORK_ABSOLUTELAYOUT_HPP
