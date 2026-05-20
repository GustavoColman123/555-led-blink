#include "lcd_i2c.h"
#include "hardware/i2c.h"

#define LCD_ADDR 0x27
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE 0x04
#define LCD_COMMAND 0x00
#define LCD_DATA 0x01

#define LCD_I2C i2c0
#define LCD_SDA_PIN 4
#define LCD_SCL_PIN 5

static void lcd_write_byte(uint8_t data)
{
    i2c_write_blocking(LCD_I2C, LCD_ADDR, &data, 1, false);
}

static void lcd_toggle_enable(uint8_t data)
{
    sleep_us(1);
    lcd_write_byte(data | LCD_ENABLE);
    sleep_us(1);
    lcd_write_byte(data & ~LCD_ENABLE);
    sleep_us(50);
}

static void lcd_send_nibble(uint8_t nibble, uint8_t mode)
{
    uint8_t data = (nibble & 0xF0) | LCD_BACKLIGHT | mode;
    lcd_write_byte(data);
    lcd_toggle_enable(data);
}

static void lcd_send_byte(uint8_t value, uint8_t mode)
{
    lcd_send_nibble(value & 0xF0, mode);
    lcd_send_nibble((value << 4) & 0xF0, mode);
}

static void lcd_command(uint8_t cmd)
{
    lcd_send_byte(cmd, LCD_COMMAND);
}

static void lcd_data(uint8_t data)
{
    lcd_send_byte(data, LCD_DATA);
}

void lcd_clear(void)
{
    lcd_command(0x01);
    sleep_ms(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t row_offsets[] = {0x00, 0x40};
    lcd_command(0x80 | (row_offsets[row] + col));
}

void lcd_string(const char *s)
{
    while (*s)
    {
        lcd_data((uint8_t)*s++);
    }
}

void lcd_init(void)
{
    i2c_init(LCD_I2C, 100 * 1000);

    gpio_set_function(LCD_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(LCD_SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(LCD_SDA_PIN);
    gpio_pull_up(LCD_SCL_PIN);

    sleep_ms(50);

    lcd_send_nibble(0x30, LCD_COMMAND);
    sleep_ms(5);
    lcd_send_nibble(0x30, LCD_COMMAND);
    sleep_us(150);
    lcd_send_nibble(0x30, LCD_COMMAND);
    sleep_us(150);
    lcd_send_nibble(0x20, LCD_COMMAND);

    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_clear();
}
