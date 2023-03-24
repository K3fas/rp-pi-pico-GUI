//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_PROGRESSBAR_HPP
#define PICO_KIT_FRAMEWORK_PROGRESSBAR_HPP

#include "include.hpp"

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::colors;

namespace rpgui::ui
{
    class ProgressBar : public View
    {
    private:
        double _progress;
        uint16_t _center; 
        uint16_t _max, _min;
        uint8_t _borderSize = 1;

    public:
        Color progressColor, borderColor;

    public:
        ProgressBar() = delete;
        ProgressBar(const ProgressBar &) = default;
        ~ProgressBar() = default;

        ProgressBar(const Point start, const Width& width, const Height& height, Color progressColor, uint16_t min, uint16_t max);
        ProgressBar(const Bounds& bounds,Color progressColor, uint16_t min, uint16_t max);

        void SetProgess(const double progress);
        void SetBorderSize(const uint8_t size);
        void SetBounds(const Bounds& bounds) final;  

        double GetProgress() const;

        void Draw() const final;

    private:
        void calculateCenter();
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_PROGRESSBAR_HPP
