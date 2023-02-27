//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_PAGE_HPP
#define PICO_KIT_FRAMEWORK_PAGE_HPP

#include <vector>
#include "../layouts/Layout.hpp"

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
        void AddLayout(const T &layout)
        {
            auto cp = new T(layout);
            auto toAdd = static_cast<Layout *>(cp);
            _children.emplace_back(toAdd);
        }
    };

} // namespace rpgui::page

#endif // PICO_KIT_FRAMEWORK_PAGE_HPP