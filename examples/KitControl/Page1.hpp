#pragma once
#include <rpgui.hpp>

using namespace rpgui;

namespace page1::model
{
    inline static struct kit_s
    {
        bool led[4];
        bool state[4];
        double progress[4];
    } data;
} // namespace page1::model

namespace page1::view
{
    using namespace page1::model;
    static inline type::ID CreatePage()
    {
        auto left = new layout::StackLayout(Point(20, 60), Width(120), Height(400));
        auto middle = new layout::StackLayout(Point(180, 60), Width(120), Height(400));
        auto right = new layout::StackLayout(Point(180+120+40, 60), Width(120), Height(400));

        left->AddElement(new ui::Label("LED On/Off"), Margin(0, 10, 0, 10));
        left->AddElement(new ui::Switch(Width(0), Height(32), data.state[0]), Margin(0, 2, 0, 2));
        left->AddElement(new ui::Switch(Width(0), Height(32), data.state[1]), Margin(0, 2, 0, 2));
        left->AddElement(new ui::Switch(Width(0), Height(32), data.state[2]), Margin(0, 2, 0, 2));
        left->AddElement(new ui::Switch(Width(0), Height(32), data.state[3]), Margin(0, 2, 0, 2));

        middle->AddElement(new ui::Label("LED Control"), Margin(0, 10, 0, 10));
        middle->AddElement(new ui::Switch(Width(0), Height(32), data.led[0]), Margin(0, 2, 0, 2));
        middle->AddElement(new ui::Switch(Width(0), Height(32), data.led[1]), Margin(0, 2, 0, 2));
        middle->AddElement(new ui::Switch(Width(0), Height(32), data.led[2]), Margin(0, 2, 0, 2));
        middle->AddElement(new ui::Switch(Width(0), Height(32), data.led[3]), Margin(0, 2, 0, 2));

        right->AddElement(new ui::Label("Led brightness"), Margin(0, 10, 0, 10));
        right->AddElement(new ui::ProgressBar(Width(0), Height(32), data.progress[0], 0, 255), Margin(0, 2, 0, 2));
        right->AddElement(new ui::ProgressBar(Width(0), Height(32), data.progress[1], 0, 255), Margin(0, 2, 0, 2));
        right->AddElement(new ui::ProgressBar(Width(0), Height(32), data.progress[2], 0, 255), Margin(0, 2, 0, 2));
        right->AddElement(new ui::ProgressBar(Width(0), Height(32), data.progress[3], 0, 255), Margin(0, 2, 0, 2));

        auto page = new Page();
        page->AddLayout(left);
        page->AddLayout(middle);
        page->AddLayout(right);
        return core::MainApp::AddPage(page);
    }
} // namespace page1::view

namespace page1::controller
{
    using namespace page1::model;

    constexpr uint LED_PINS[] = {6, 7, 8, 9};
    constexpr uint POTENTIOMETER = 27;
    constexpr uint POTENTIOMETER_ADC = 1;

    void on_pwm_wrap()
    {
        // Clear the interrupt flag that brought us here
        pwm_clear_irq(pwm_gpio_to_slice_num(LED_PINS[0]));
        for (size_t i = 0; i < 4; i++)
        {
            if (data.led[i])
            {
                data.progress[i] = (double)(adc_read() >> 4); // read adc value
            }
        }
    }

    void Init()
    {
        // adc initialization
        adc_init();
        // make sure GPIO is high-impedance, no pullups etc
        adc_gpio_init(POTENTIOMETER);
        // select ADC input
        adc_select_input(POTENTIOMETER_ADC);

        // Get some sensible defaults for the slice configuration. By default, the
        // counter is allowed to wrap over its maximum range (0 to 2**16-1)
        pwm_config config = pwm_get_default_config();
        // Set divider, reduces counter clock to sysclock/this value
        pwm_config_set_clkdiv(&config, 4.f);

        for (size_t i = 0; i < 4; i++)
        {
            gpio_set_function(LED_PINS[i], GPIO_FUNC_PWM);
            uint slice_num = pwm_gpio_to_slice_num(LED_PINS[i]);
            pwm_set_gpio_level(LED_PINS[i], 0);
            pwm_init(slice_num, &config, true);
        }

        // Mask our slice's IRQ output into the PWM block's single interrupt line,
        // and register our interrupt handler
        pwm_clear_irq(pwm_gpio_to_slice_num(LED_PINS[0]));
        pwm_set_irq_enabled(pwm_gpio_to_slice_num(LED_PINS[0]), true);
        irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
        irq_set_enabled(PWM_IRQ_WRAP, true);
    }

    void Update()
    {
        for (size_t i = 0; i < 4; i++)
        {
            if (data.state[i])
            {
                pwm_set_gpio_level(LED_PINS[i], data.progress[i] * data.progress[i]);
            }
            else
            {
                pwm_set_gpio_level(LED_PINS[i], 0);
            }
        }
    }

} // namespace page1::controller
