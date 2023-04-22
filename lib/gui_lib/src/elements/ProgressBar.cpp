//
// Created by kefas on 26.2.23.
//

#include "ProgressBar.hpp"
#include "IVGA.hpp"

rpgui::ui::ProgressBar::ProgressBar(const Width &width, const Height &height, const double &progress, uint16_t min, uint16_t max,
                                    Color backgorundColor, Color progressColor, Color borderColor)
    : View(Bounds(0, 0, width.v, height.v), backgorundColor), _max(max), _min(min), progress(progress), progressColor(progressColor), borderColor(borderColor)
{
}

rpgui::ui::ProgressBar::ProgressBar(const Width &width, const Height &height, double &progress, uint16_t min, uint16_t max,
                                    Color backgorundColor, Color progressColor, Color borderColor)
    : View(Bounds(0, 0, width.v, height.v), backgorundColor), _max(max), _min(min), progress(progress), progressColor(progressColor), borderColor(borderColor)
{
}

rpgui::ui::ProgressBar::ProgressBar(const Bounds &bounds, const double &progress, uint16_t min, uint16_t max,
                                    Color backgorundColor, Color progressColor, Color borderColor)
    : View(bounds, backgorundColor), _max(max), _min(min), progress(progress), progressColor(progressColor), borderColor(borderColor)
{
}

rpgui::ui::ProgressBar::ProgressBar(const Bounds &bounds, double &progress, uint16_t min, uint16_t max,
                                    Color backgorundColor, Color progressColor, Color borderColor)
    : View(bounds, backgorundColor), _max(max), _min(min), progress(progress),  progressColor(progressColor), borderColor(borderColor)
{
}

void rpgui::ui::ProgressBar::SetBounds(const Bounds &bounds)
{
    rpgui::common::VisualElement::SetBounds(bounds);
}

void rpgui::ui::ProgressBar::SetBorderSize(const uint8_t size)
{
    _borderSize = size;
}

void rpgui::ui::ProgressBar::Draw() const
{
    auto center = rpgui::ui::ProgressBar::getNewCenter();
    auto bounds = this->GetBounds();
    IVGA::IDrawRectangle(Bounds(bounds.x, bounds.y, center, bounds.h), progressColor);
    IVGA::IDrawRectangle(Bounds(bounds.x + center, bounds.y, bounds.w - center, bounds.h), color);
    IVGA::IDrawFrame(bounds, borderColor);
}

void rpgui::ui::ProgressBar::calculateCenter()
{
    // adjusted for border size
    auto width = this->GetBounds().w - _borderSize * 2;
    auto nom = (width* progress.GetValue());
    _center =  nom / (_max - _min) ;
}

uint16_t rpgui::ui::ProgressBar::getNewCenter() const
{
    // adjusted for border size
    auto width = this->GetBounds().w - _borderSize * 2;
    double val = progress.GetValue();
    if (val > _max)
    {
        val = _max;
    }
    if(val < _min)
    {
        val = _min;
    }
    
    auto nom = (width* val);
    return nom / (_max - _min) ;
}
