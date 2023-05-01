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
    class ProgressBar : public VisualElement
    {
    private:
        uint16_t _center;
        const uint16_t _max, _min;
        uint8_t _borderSize = 1;

    public:
        BindableProperty<double> progress;
        Color progressColor, borderColor;

    public:
        ProgressBar() = delete;
        ProgressBar(const ProgressBar &) = default;
        ~ProgressBar() = default;

        ProgressBar(const Width &width, const Height &height, const double &progress, uint16_t min = 0, uint16_t max = 100,
                    Color backgorundColor = Color::SemiGray,
                    Color progressColor = Color::Red,
                    Color borderColor = Color::Gray);

        ProgressBar(const Width &width, const Height &height, double &progress, uint16_t min = 0, uint16_t max = 100,
                    Color backgorundColor = Color::SemiGray,
                    Color progressColor = Color::Red,
                    Color borderColor = Color::Gray);

        ProgressBar(const Bounds &bounds, const double &progress, uint16_t min = 0, uint16_t max = 100,
                    Color backgorundColor = Color::SemiGray,
                    Color progressColor = Color::Red,
                    Color borderColor = Color::Gray);

        ProgressBar(const Bounds &bounds, double &progress, uint16_t min = 0, uint16_t max = 100,
                    Color backgorundColor = Color::SemiGray,
                    Color progressColor = Color::Red,
                    Color borderColor = Color::Gray);

        void SetBorderSize(const uint8_t size);
        void SetBounds(const Bounds &bounds) final;

        void Draw() const final;

        void Test();

    private:
        void calculateCenter();
        uint16_t getNewCenter() const;
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_PROGRESSBAR_HPP
