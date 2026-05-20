#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "lcd_i2c.h"

#define LED_PIN 10
#define SERVO_PIN 15
#define BUTTON_PIN 16

#define DEBOUNCE_MS 200

#define SERVO_IDLE_US 1500
#define SERVO_FOCUS_US 1000
#define SERVO_BREAK_US 2000
#define SERVO_ALERT_US 1200

typedef enum {
    STATE_IDLE,
    STATE_FOCUS,
    STATE_BREAK,
    STATE_ALERT,
    STATE_COUNT
} system_state_t;

static void servo_set_us(uint gpio, uint pulse_us)
{
    pwm_set_gpio_level(gpio, pulse_us);
}

static void servo_init(uint gpio)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(gpio);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125.0f);
    pwm_config_set_wrap(&config, 20000);

    pwm_init(slice_num, &config, true);
}

static void lcd_show_state(system_state_t state)
{
    lcd_clear();

    lcd_set_cursor(0, 0);
    lcd_string("DESK TERMINAL");

    lcd_set_cursor(1, 0);

    switch (state)
    {
        case STATE_IDLE:
            lcd_string("STATUS: IDLE");
            break;

        case STATE_FOCUS:
            lcd_string("MODE: FOCUS");
            break;

        case STATE_BREAK:
            lcd_string("MODE: BREAK");
            break;

        case STATE_ALERT:
            lcd_string("MODE: ALERT");
            break;

        default:
            lcd_string("SYSTEM ERROR");
            break;
    }
}

static void apply_state(system_state_t state)
{
    lcd_show_state(state);

    switch (state)
    {
        case STATE_IDLE:
            gpio_put(LED_PIN, 0);
            servo_set_us(SERVO_PIN, SERVO_IDLE_US);
            break;

        case STATE_FOCUS:
            gpio_put(LED_PIN, 1);
            servo_set_us(SERVO_PIN, SERVO_FOCUS_US);
            break;

        case STATE_BREAK:
            servo_set_us(SERVO_PIN, SERVO_BREAK_US);
            break;

        case STATE_ALERT:
            servo_set_us(SERVO_PIN, SERVO_ALERT_US);
            break;

        default:
            gpio_put(LED_PIN, 0);
            servo_set_us(SERVO_PIN, SERVO_IDLE_US);
            break;
    }
}

static void update_led_pattern(system_state_t state)
{
    static absolute_time_t last_toggle_time;
    static bool led_state = false;
    static bool initialized = false;

    if (!initialized)
    {
        last_toggle_time = get_absolute_time();
        initialized = true;
    }

    int blink_interval_ms = 0;

    switch (state)
    {
        case STATE_IDLE:
            gpio_put(LED_PIN, 0);
            return;

        case STATE_FOCUS:
            gpio_put(LED_PIN, 1);
            return;

        case STATE_BREAK:
            blink_interval_ms = 700;
            break;

        case STATE_ALERT:
            blink_interval_ms = 150;
            break;

        default:
            gpio_put(LED_PIN, 0);
            return;
    }

    int64_t elapsed_ms =
        absolute_time_diff_us(last_toggle_time, get_absolute_time()) / 1000;

    if (elapsed_ms >= blink_interval_ms)
    {
        led_state = !led_state;
        gpio_put(LED_PIN, led_state);
        last_toggle_time = get_absolute_time();
    }
}

int main(void)
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    servo_init(SERVO_PIN);
    lcd_init();

    system_state_t current_state = STATE_IDLE;
    apply_state(current_state);

    bool previous_button = false;
    absolute_time_t last_press_time = get_absolute_time();

    while (true)
    {
        bool button_pressed = !gpio_get(BUTTON_PIN);
        bool rising_edge = button_pressed && !previous_button;

        int64_t elapsed_ms =
            absolute_time_diff_us(last_press_time, get_absolute_time()) / 1000;

        if (rising_edge && elapsed_ms > DEBOUNCE_MS)
        {
            current_state = (current_state + 1) % STATE_COUNT;
            apply_state(current_state);
            last_press_time = get_absolute_time();
        }

        update_led_pattern(current_state);

        previous_button = button_pressed;

        sleep_ms(10);
    }
}