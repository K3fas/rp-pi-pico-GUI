//
// Created by kefas on 26.2.23.
//
#include "Button.hpp"
#include "Label.hpp"
#include "rp_core.hpp"
#include "IVGA.hpp"

rpgui::ui::Button::~Button()
{
    delete(_text);
}

rpgui::ui::Button::Button(const Width &width, const Height &heigth, const Color &color,
                          std::string &text, const Color &textColor, uint8_t fontSize, void *font)
    : View(Bounds(0, 0, width.v, heigth.v), color), _text(new Label(text, textColor))
{
}

rpgui::ui::Button::Button(const Width &width, const Height &heigth, const Color &color,
                          const std::string &text, const Color &textColor, uint8_t fontSize, void *font)
    : View(Bounds(0, 0, width.v, heigth.v), color), _text(new Label(text, textColor))
{
}

rpgui::ui::Button::Button(const Bounds &bounds, const Color &color, std::string &text, const Color &textColor, uint8_t fontSize, void *font)
    : View(bounds, color), _text(new Label(text, textColor))
{
}

rpgui::ui::Button::Button(const Bounds &bounds, const Color &color, const std::string &text, const Color &textColor, uint8_t fontSize, void *font)
    : View(bounds, color), _text(new Label(text, textColor))
{
}

void rpgui::ui::Button::SetText(const std::string &text)
{
    _text->SetText(text);
}

void rpgui::ui::Button::SetBounds(const Bounds &bounds)
{
    this->rpgui::common::View::SetBounds(bounds);
    // Put text to center of button
    auto textBounds = _text->GetBounds();
    textBounds.x = bounds.x + (bounds.w - textBounds.w) / 2;
    textBounds.y = bounds.y + (bounds.h - textBounds.h) / 2;
    _text->SetBounds(textBounds);
}

void rpgui::ui::Button::Draw() const
{
#ifdef TRACKING
    auto start = time_us_32();
#endif
    IVGA::IDrawRectangle(this->GetBounds(), this->color);
    if (!_text->text.GetValue().empty())
    {
        _text->Draw();
    }
#ifdef TRACKING
    printf("Button Draw took %f\n", time_us_32() - start);
#endif
}
