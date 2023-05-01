//
// Created by kefas on 26.2.23.
//

#include "common/View.hpp"
#include "common/Base.hpp"
#include "common/Types.hpp"
#include "View.hpp"

using namespace rpgui::common;

rpgui::common::View::~View()
{
    for (auto element : _children)
    {
        delete element;
    }
}

const std::vector<VisualElement *> &rpgui::common::View::GetChildren() const
{
    return _children;
}

ID rpgui::common::View::AddChildren(VisualElement *child)
{
    _children.push_back(child);
    return child->GetId();
}

ID rpgui::common::View::SetActive(VisualElement *element)
{
    _activeElement = element;
    return element->GetId();
}

VisualElement *rpgui::common::View::GetActive() const
{
    return _activeElement;
}
