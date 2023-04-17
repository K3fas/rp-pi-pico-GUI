#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pio.h"
#include "hardware/timer.h"

#include "quadrature_encoder.pio.h"

#include "bsp/board.h"
#include "tusb.h"

#include <rpgui.hpp>

#include <string>  

using namespace rpgui::ui;
using namespace rpgui::common;
using namespace rpgui::type;
using namespace rpgui::colors;

Page *InitPage();

void AddPages();

#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9

#define POTENTIOMETER 27        // input gpio for potentiometer
#define POTENTIOMETER_ADC_CH 1  // input channel of adc

#define PIN_AB 21

struct
{
    bool led1 = false;
    bool led2 = false;
    bool led3 = false;
    bool led4 = false;
    double potValue = 0;
    int counter =0;
    std::string counterStr ="";

} page;

void initAll()
{
    stdio_init_all();
    board_init();
    tusb_init();

    // adc initialization
    adc_init();
    // make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(POTENTIOMETER);
    // select ADC input
    adc_select_input(POTENTIOMETER_ADC_CH);


    gpio_init(LED1);
    gpio_init(LED2);
    gpio_init(LED3);
    gpio_init(LED4);

    gpio_set_dir(LED1, GPIO_OUT);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_set_dir(LED3, GPIO_OUT);
    gpio_set_dir(LED4, GPIO_OUT);

    
}

int main()
{
    initAll();

    AddPages();

    PIO pio = pio1;
    const uint sm = 0;

    uint offset = pio_add_program(pio, &quadrature_encoder_program);
    quadrature_encoder_program_init(pio, sm, offset, PIN_AB, 0);

    while (1)
    {
        gpio_put(LED1, page.led1);
        gpio_put(LED2, page.led2);
        gpio_put(LED3, page.led3);
        gpio_put(LED4, page.led4);

        page.potValue = adc_read() >> 4;

        page.counter = quadrature_encoder_get_count(pio, sm);
        page.counterStr = std::to_string(page.counter);

        rpgui::core::MainApp::Update();
    }
}

Page *InitPage()
{
    auto ret = new rpgui::page::Page();
    auto lay1 = new rpgui::layout::StackLayout(Point(60, 120), Width(40), Height(200));
    lay1->AddElement(new Label("LEDs:"));
    lay1->AddElement(new Switch(Width(0), Height(10), page.led1));
    lay1->AddElement(new Switch(Width(0), Height(10), page.led2));
    lay1->AddElement(new Switch(Width(0), Height(10), page.led3));
    lay1->AddElement(new Switch(Width(0), Height(10), page.led4));

    auto lay2 = new rpgui::layout::StackLayout(Point(120, 120), Width(100), Height(200));
    lay2->AddElement(new Label("Potentiometer"));
    lay2->AddElement(new ProgressBar(Width(0), Height(20),page.potValue,0,255));
    lay2->AddElement(new Label("Encoder"));
    lay2->AddElement(new Label(page.counterStr));


    ret->AddLayout(lay1);
    ret->AddLayout(lay2);
    return ret;
}

void AddPages()
{
    rpgui::core::MainApp::AddPage(InitPage());
}
