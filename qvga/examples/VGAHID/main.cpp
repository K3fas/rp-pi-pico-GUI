
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/float.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "bsp/board.h"
#include "tusb.h"
#include "tusb_data.hpp"

#include "pong.hpp"
#include "IVGA.hpp"

#include "qvga/qvga.h" // QVGA core
// #include "qvga/draw.h" // draw
#include "qvga/rand.h" // random number generator

#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9

#define DAC_BUTTONS 28       // input gpio for dac buttons
#define DAC_BUTTONS_ADC_CH 2 // input channel of adc

using namespace IVGA;
using namespace UI;

extern HID::KBD_t KBD;
extern HID::MOUSE_t MOUSE;

static struct timers_s
{
    uint64_t startTime, renderTime, hidTime, processInputTime, gameUpdateTime, vSyncTime;
} timers;

void LED_blink_task();
void ProcessButtons(bool *buttons);
void PrintTimings();

extern void cdc_task(void);
extern void hid_app_task(void);

void SetupRP()
{
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(DAC_BUTTONS);
    adc_select_input(DAC_BUTTONS_ADC_CH);

    gpio_init(LED1);
    gpio_init(LED2);
    gpio_init(LED3);
    gpio_init(LED4);

    gpio_set_dir(LED1, GPIO_OUT);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_set_dir(LED3, GPIO_OUT);
    gpio_set_dir(LED4, GPIO_OUT);

#ifndef PICO_DEFAULT_LED_PIN
#warning regular LED pin not found
#else
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, true);
#endif
}

int main()
{
    adc_init();
    board_init();
    stdio_init_all();
    tusb_init();

    printf("VGA HID Example\r\n");
    sleep_ms(2000);

    SetupRP();

    auto game = Pong::PongGame();
    game.Init();

    auto view = View();

    auto rect = new UI::Rectangle(IVGA::Rectangle({50, 50}, Width{50}, Height{50}), VColors::Color::DarkCyan);
    view.AddElement(rect);
    std::vector<UI::Drawable *> vect = std::vector<UI::Drawable *>();

    for (int i = 0; i < WIDTH * 10; i++)
    {
        view.AddElement(new UI::Rectangle(IVGA::Rectangle(Point(i % WIDTH, i % 20), Width{1}, Height{1}), VColors::Color::Red));
    }

    view.AddElement(new UI::Label("test", IVGA::Point(80, 120), VColors::Color::Blue));

    while (1)
    {

        timers.startTime = time_us_64();

        game.Render();
        timers.renderTime = time_us_64() - timers.startTime;

        tuh_task();
        hid_app_task();
        timers.hidTime = time_us_64() - timers.renderTime - timers.startTime;

        ProcessButtons(Pong::buttons);
        timers.processInputTime = time_us_64() - timers.hidTime - timers.startTime;

        game.Update(1);
        timers.gameUpdateTime = time_us_64() - timers.processInputTime - timers.startTime;
        Core1Wait();
        WaitVSync();
        timers.vSyncTime = time_us_64() - timers.gameUpdateTime - timers.startTime;

        // timers.startTime = time_us_64();
        // view.DrawAll();
        // timers.renderTime = time_us_64() - timers.startTime;
        // WaitVSync();
        // timers.vSyncTime = time_us_64() - timers.renderTime - timers.startTime;

        LED_blink_task();

        PrintTimings();
    }
}

void ProcessButtons(bool *buttons)
{
    // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
    const float conversion_factor = 3.3f / ((1 << 12) - 1);
    uint16_t result = adc_read();
    float voltage = result * conversion_factor;

    uint8_t base = round(16 * voltage / 3.3f);

    buttons[0] = false;
    buttons[1] = false;
    buttons[2] = false;
    buttons[3] = false;
    for (size_t i = 0; i < 6; i++)
    {
        if (KBD.pressedKeys[i] == 'w')
        {
            buttons[0] = true;
        }
        if (KBD.pressedKeys[i] == 's')
        {
            buttons[1] = true;
        }
        if (KBD.pressedKeys[i] == 'i')
        {
            buttons[2] = true;
        }
        if (KBD.pressedKeys[i] == 'k')
        {
            buttons[3] = true;
        }
    }

    buttons[0] = buttons[0] || base & 0b1000;
    buttons[1] = buttons[1] || base & 0b0100;
    buttons[2] = buttons[2] || base & 0b0010;
    buttons[3] = buttons[3] || base & 0b0001;

    gpio_put(LED1, buttons[0]);
    gpio_put(LED2, buttons[1]);
    gpio_put(LED3, buttons[2]);
    gpio_put(LED4, buttons[3]);
}

void PrintTimings()
{
    const uint32_t interval_on_ms = 1000;
    static uint32_t start_ms = 0;

    // Blink every interval ms
    if (board_millis() - start_ms < interval_on_ms)
        return; // not enough time

    start_ms += interval_on_ms;

    printf("Timing report, one frame is 16 ms\n");
    printf("Start time: %lld us\n", timers.startTime);
    printf("Render time: %lld us          %f %% \n", timers.renderTime, ((float)timers.renderTime / (1 / 0.006)));
    printf("HID time: %lld us             %f %% \n", KBD.processTime, ((float)KBD.processTime / (1 / 0.006)));
    printf("Process input time: %lld us   %f %%   \n", timers.processInputTime, ((float)timers.hidTime / (1 / 0.006)));
    printf("Game update time: %lld us     %f %% \n", timers.gameUpdateTime, ((float)timers.gameUpdateTime / (1 / 0.006)));
    printf("Vsync time: %lld us           %f %%\n\n", timers.vSyncTime, ((float)timers.vSyncTime / (1 / 0.006)));

    KBD.processTime = 0;
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
#if CFG_TUH_CDC
CFG_TUSB_MEM_SECTION static char serial_in_buffer[64] = {0};

void tuh_mount_cb(uint8_t dev_addr)
{
    // application set-up
    printf("A device with address %d is mounted\r\n", dev_addr);

    tuh_cdc_receive(dev_addr, serial_in_buffer, sizeof(serial_in_buffer), true); // schedule first transfer
}

void tuh_umount_cb(uint8_t dev_addr)
{
    // application tear-down
    printf("A device with address %d is unmounted \r\n", dev_addr);
}

// invoked ISR context
void tuh_cdc_xfer_isr(uint8_t dev_addr, xfer_result_t event, cdc_pipeid_t pipe_id, uint32_t xferred_bytes)
{
    (void)event;
    (void)pipe_id;
    (void)xferred_bytes;

    printf(serial_in_buffer);
    tu_memclr(serial_in_buffer, sizeof(serial_in_buffer));

    tuh_cdc_receive(dev_addr, serial_in_buffer, sizeof(serial_in_buffer), true); // waiting for next data
}

void cdc_task(void)
{
}

#endif

//--------------------------------------------------------------------+
// TinyUSB Callbacks
//--------------------------------------------------------------------+

void LED_blink_task()
{
    const uint32_t interval_on_ms = 500;
    const uint32_t interval_off_ms = 4500;
    static uint32_t start_ms = 0;

    static bool led_state = false;

    // Blink every interval ms
    if (board_millis() - start_ms < interval_off_ms)
        return; // not enough time

    if (led_state)
    {
        start_ms += interval_on_ms;
        auto val = gpio_get(24);
        printf("VBUS Voltage: %d\r\n", val);
    }
    else
    {
        start_ms += interval_off_ms;
    }

    gpio_put(PICO_DEFAULT_LED_PIN, led_state);
    led_state = 1 - led_state; // toggle
}