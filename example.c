
#include "app_btn.h"

#define APP_BTN_MAX_BTN_SUPPORT     2


void on_button_event_cb(int button_pin, int event, void *data)
{
    static const char *event_name[] = {"pressed", "release", "hold", "hold so long", "double click", "tripple click", "idle", "idle break", "invalid"};
    DEBUG_PRINTF("Button %d, event %s\r\n", button_pin, event_name[event]);

    switch (event)
    {
    case APP_BTN_EVT_PRESSED:
        break;

    case APP_BTN_EVT_RELEASED:
        break;

    case APP_BTN_EVT_HOLD:
        break;

    case APP_BTN_EVT_DOUBLE_CLICK:
    {
    }
    break;

    case APP_BTN_EVT_HOLD_SO_LONG:
    {
    }
    break;

    default:
        DEBUG_PRINTF("[%s] Unhandle button event %d\r\n", __FUNCTION__, event);
        break;
    }
}

uint32_t board_hw_button_read(uint32_t pin)
{
    if (pin == BOARD_HW_BUTTON_0)       // pair
    {
        return gpio_input_bit_get(GPIOA, GPIO_PIN_10);
    }
    else if (pin == BOARD_HW_BUTTON_1)  // on/off
    {
        return gpio_input_bit_get(GPIOA, GPIO_PIN_9);
    }
    else if (pin == BOARD_HW_BUTTON_2)
    {
        
    }
    return 0;
}

uint32_t sys_now_ms(void)
{
    return m_sys_tick_ms;
}

static void button_init(void)
{
    static app_btn_hw_config_t m_hw_button_initialize_value[APP_BTN_MAX_BTN_SUPPORT];

    for (uint32_t i = 0; i < APP_BTN_MAX_BTN_SUPPORT; i++)
    {
        m_hw_button_initialize_value[i].idle_level = 1;
        m_hw_button_initialize_value->last_state = board_hw_button_read(i); // read the very first level at initialization
        m_hw_button_initialize_value->pin = i;
    }

    app_btn_config_t conf;
    conf.config = &m_hw_button_initialize_value[0];
    conf.btn_count = APP_BTN_MAX_BTN_SUPPORT;
    conf.get_tick_cb = sys_now_ms;
    conf.btn_initialize = NULL;
    conf.btn_read = board_hw_button_read;

    app_btn_initialize(&conf);
    app_btn_register_callback(APP_BTN_EVT_PRESSED, on_button_event_cb, NULL);
    app_btn_register_callback(APP_BTN_EVT_RELEASED, on_button_event_cb, NULL);
    app_btn_register_callback(APP_BTN_EVT_TRIPLE_CLICK, on_button_event_cb, NULL);
}

void main(void)
{
    button_init();

    while (1)
    {
        app_btn_scan(NULL);
    }
}