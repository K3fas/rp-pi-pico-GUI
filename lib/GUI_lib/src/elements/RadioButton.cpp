//
// Created by kefas on 26.2.23.
//
#include "RadioButton.hpp"
#include "IVGA.hpp"
#include "MouseDispatcher.hpp"
#include "rp_core.hpp"

using namespace rpgui::core;

rpgui::ui::RadioButton::RadioButton(const Width &itemWidth, const Height &itemHeight,
                                    Color color, Color bgColor,
                                    const void *font, uint8_t fontSize)
    : View(Bounds(0, 0, itemWidth.v, 0), color),
      _itemHeight(itemHeight.v),
      _itemWidth(itemWidth.v),
      _fontSize(fontSize),
      _font(font),
      backgorundColor(bgColor)
{
    MainApp::AddListener(MouseEventType::Clicked, rpgui::event::Handler(clickHandler, this));
}

void rpgui::ui::RadioButton::AddItem(std::string text)
{
    auto bounds = GetBounds();
    bounds.h += _itemHeight;
    SetBounds(bounds);

    // TODO: Add as label ?
    _items.push_back(text);
}

void rpgui::ui::RadioButton::SetBounds(const Bounds &bounds)
{
    VisualElement::SetBounds(bounds);

    _delimiter = bounds.w / 5;
    _circleCenter.x = bounds.x + _delimiter / 2;
    _circleCenter.y = bounds.y + _itemHeight / 2;
}

void rpgui::ui::RadioButton::Draw() const
{
    auto bounds = GetBounds();
    IVGA::IDrawRectangle(this->GetBounds(), backgorundColor);
    for (uint8_t i = 0; i < _items.size(); i++)
    {
        if (i != checkedItem)
        {
            IVGA::IDrawCircle(Point(_circleCenter.x, _circleCenter.y + i * _itemHeight), Radius(circleRadius), color, false);
        }
        else
        {
            IVGA::IDrawCircle(Point(_circleCenter.x, _circleCenter.y + i * _itemHeight), Radius(circleRadius), color, true);
        }

        IVGA::IDrawText(_items.at(i).c_str(), Point(bounds.x + _delimiter, bounds.y + _itemHeight * i + _fontSize / 2), color);
    }
}

void rpgui::ui::RadioButton::clickHandler(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender)
{
    auto btn = (RadioButton *)sender;
    auto bounds = btn->GetBounds();
    for (uint8_t i = 0; i < btn->_items.size(); i++)
    {
        auto itemBounds = Bounds(bounds.x, bounds.y + i * btn->_itemHeight, bounds.w, btn->_itemHeight);
        if (IsInBounds(itemBounds, Point(event.xPos, event.yPos)))
        {
            btn->_checkedItem = i;
            event.SetHandled();
            return;
        }
    }
}
