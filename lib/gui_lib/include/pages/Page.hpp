//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_PAGE_HPP
#define PICO_KIT_FRAMEWORK_PAGE_HPP

#include <vector>
#include "Layout.hpp"
#include <type_traits>

using namespace rpgui::layout;

namespace rpgui::page
{
    class Page : public rpgui::common::Element
    {
    private:
        std::vector<Layout *> _children;

    public:
        Page() = default;
        Page(const Page &) = default;
        ~Page() = default;

        virtual void Draw()
        {
            for (auto &&child : _children)
            {
                child->Draw();
            }
        }

        template <typename T>
            requires std::is_base_of<Layout, T>::value
        void AddLayout( T *layout)
        {
            _children.emplace_back((Layout*) layout);
        }
    };

} // namespace rpgui::page

#endif // PICO_KIT_FRAMEWORK_PAGE_HPP