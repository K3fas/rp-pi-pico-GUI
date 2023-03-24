//
// Created by kefas on 26.2.23.
//
#include "Layout.hpp"

rpgui::layout::Layout::~Layout()
{
    for (auto &&element : _children)
    {
        delete element;
    }
}

rpgui::layout::Layout::Layout(const Bounds coords, Color bgColor)
     : View(coords, bgColor)
{
}

const std::vector<View *> &rpgui::layout::Layout::GetChildren() const
{
    return _children;
}
