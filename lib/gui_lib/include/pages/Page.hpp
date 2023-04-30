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

        Page(Layout *layout)
        {
            _children.push_back(layout);
        }

        virtual void Draw()
        {
            for (auto &&child : _children)
            {
                child->Draw();
            }
        }

        void AddLayout(Layout *layout)
        {
            _children.push_back(layout);
        }
    };

} // namespace rpgui::page

#endif // PICO_KIT_FRAMEWORK_PAGE_HPP