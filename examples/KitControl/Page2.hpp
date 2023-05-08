#pragma once
#include <rpgui.hpp>
#include <string>
#include "quadrature_encoder.pio.h"

namespace page2::model
{
    inline static struct data_s
    {
        uint16_t encoder = 0;
        uint16_t counter = 0;
        ui::Label *counter_lbl;

        data_s &operator++()
        {
            ++counter;
            return *this;
        }

        data_s &operator--()
        {
            --counter;
            return *this;
        }
    } data;
} // namespace page2::model

namespace page2::view
{
    using namespace page2::model;
    static inline type::ID CreatePage()
    {
        auto middle = new layout::StackLayout(Point(180, 60), Width(120), Height(400));
        middle->AddElement(new ui::Label("LED Counter"), Margin(0, 10, 0, 10));
        auto lbl = new ui::Label("0");
        data.counter_lbl = lbl;
        middle->AddElement(lbl), Margin(0, 10, 0, 10);
        middle->AddElement(new ui::Stepper<uint16_t>(Width(120), Height(32), data.counter), Margin(0, 2, 0, 2));

        auto page = new Page();
        page->AddLayout(middle);
        return core::MainApp::AddPage(page);
    }
} // namespace page2::view

namespace page2::controller
{
    using namespace page2::model;

    constexpr uint LED_PINS[] = {6, 7, 8, 9};
    constexpr uint EXPANDER_CS_PIN = 26;
    constexpr uint PIN_AB = 21;

    void Init()
    {
        stdio_init_all();

        PIO pio = pio1;
        const uint sm = 0;

        uint offset = pio_add_program(pio, &quadrature_encoder_program);
        quadrature_encoder_program_init(pio, sm, offset, PIN_AB, 0);

        for (size_t i = 0; i < 4; i++)
        {
            gpio_init(LED_PINS[i]);
            gpio_set_dir(LED_PINS[i], GPIO_OUT);
        }
    }

    void Update()
    {
        PIO pio = pio1;
        const uint sm = 0;
        data.encoder = quadrature_encoder_get_count(pio, sm);
        data.counter_lbl->SetText(std::to_string(data.encoder / 4 + data.counter));
        gpio_put(LED_PINS[0], ((data.encoder / 4) + data.counter) & 0b1000);
        gpio_put(LED_PINS[1], ((data.encoder / 4) + data.counter) & 0b0100);
        gpio_put(LED_PINS[2], ((data.encoder / 4) + data.counter) & 0b0010);
        gpio_put(LED_PINS[3], ((data.encoder / 4) + data.counter) & 0b0001);
    }
} // namespace page2::controller
