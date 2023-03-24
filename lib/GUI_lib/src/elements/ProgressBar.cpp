//
// Created by kefas on 26.2.23.
//

#include "ProgressBar.hpp"
#include "IVGA.hpp"

rpgui::ui::ProgressBar::ProgressBar(const Point start, const Width &width, const Height &height, Color progressColor, uint16_t min, uint16_t max)
    : View(Bounds(start.x, start.y, width.v, height.v), Color::SemiGray), _max(max), _min(min), progressColor(progressColor), borderColor(Color::Gray)
{
}

rpgui::ui::ProgressBar::ProgressBar(const Bounds &bounds, Color progressColor, uint16_t min, uint16_t max)
    : View(bounds, Color::SemiGray), _max(max), _min(min), progressColor(progressColor), borderColor(Color::Gray)
{
}

void rpgui::ui::ProgressBar::SetProgess(const double progress)
{
    _progress = progress;
    if (progress > _max)
        _progress = _max;
    if (progress < _min)
        _progress = _min;

    // calculate center line of progress bar
    calculateCenter();
}

void rpgui::ui::ProgressBar::SetBounds(const Bounds &bounds)
{
    rpgui::common::VisualElement::SetBounds(bounds);
    calculateCenter();
}

void rpgui::ui::ProgressBar::SetBorderSize(const uint8_t size)
{
    _borderSize = size;
}

double rpgui::ui::ProgressBar::GetProgress() const
{
    return _progress;
}

void rpgui::ui::ProgressBar::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawFrame(bounds, borderColor);
    bounds = bounds - _borderSize;
    IVGA::IDrawRectangle(Bounds(bounds.x, bounds.y, _center, bounds.h), progressColor);
    IVGA::IDrawRectangle(Bounds(bounds.x + _center, bounds.y, bounds.w - _center, bounds.h), color);
}

void rpgui::ui::ProgressBar::calculateCenter()
{
#ifdef TRACKING
    auto start = time_us_32();
#endif
    // adjusted for border size
    auto width = this->GetBounds().w - _borderSize * 2;
    auto nom = ((_max - _min) * _progress);
    _center = nom / width;
#ifdef TRACKING
    printf("ProgressBar Draw took %f\n", time_us_32() - start);
#endif
}
