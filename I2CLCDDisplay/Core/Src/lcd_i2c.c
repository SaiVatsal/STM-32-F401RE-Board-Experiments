/*
 * lcd_i2c.c
 *
 * I2C LCD driver (PCF8574 backpack) for STM32F401RE
 * I2C1: PB6 = SCL, PB7 = SDA
 */

#include "lcd_i2c.h"

/* PCF8574 bit mapping (standard LCD I2C backpack wiring):
 * P0 -> RS
 * P1 -> RW
 * P2 -> EN
 * P3 -> Backlight
 * P4 -> D4
 * P5 -> D5
 * P6 -> D6
 * P7 -> D7
 */

static uint8_t backlight_state = 0x08; /* backlight ON by default */

/* Low level: write one byte to the PCF8574 over I2C */
static void LCD_I2C_Write(uint8_t data)
{
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, &data, 1, HAL_MAX_DELAY);
}

/* Pulse the Enable pin to latch data into the LCD */
static void LCD_EnablePulse(uint8_t data)
{
    HAL_Delay(1);
    LCD_I2C_Write(data | 0x04); /* EN = 1 */
    HAL_Delay(1);
    LCD_I2C_Write(data & ~0x04); /* EN = 0 */
    HAL_Delay(1);
}

/* Send 4 bits (upper nibble of 'nibble' parameter is used) */
static void LCD_Write4Bits(uint8_t nibble, uint8_t mode)
{
    uint8_t data = (nibble & 0xF0) | backlight_state | mode;
    LCD_I2C_Write(data);
    LCD_EnablePulse(data);
}

/* Send a full byte, splitting into two nibbles.
 * mode = 0x00 for command, 0x01 for data (RS pin)
 */
static void LCD_Send(uint8_t value, uint8_t mode)
{
    LCD_Write4Bits(value & 0xF0, mode);        /* high nibble */
    LCD_Write4Bits((value << 4) & 0xF0, mode);  /* low nibble */
}

static void LCD_Command(uint8_t cmd)
{
    LCD_Send(cmd, 0x00);
}

void LCD_SendChar(char c)
{
    LCD_Send((uint8_t)c, 0x01);
}

void LCD_SendString(char *str)
{
    while (*str)
    {
        LCD_SendChar(*str++);
    }
}

void LCD_Backlight(uint8_t state)
{
    backlight_state = state ? 0x08 : 0x00;
    LCD_I2C_Write(backlight_state);
}

void LCD_Clear(void)
{
    LCD_Command(0x01);
    HAL_Delay(2); /* clear command needs extra time */
}

void LCD_Home(void)
{
    LCD_Command(0x02);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t col, uint8_t row)
{
    uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row >= LCD_ROWS) row = LCD_ROWS - 1;
    LCD_Command(0x80 | (col + row_offsets[row]));
}

void LCD_Init(void)
{
    HAL_Delay(50); /* wait for LCD power-up */

    /* Initialization sequence for 4-bit mode (HD44780 datasheet) */
    LCD_Write4Bits(0x30, 0x00);
    HAL_Delay(5);
    LCD_Write4Bits(0x30, 0x00);
    HAL_Delay(1);
    LCD_Write4Bits(0x30, 0x00);
    HAL_Delay(1);
    LCD_Write4Bits(0x20, 0x00); /* switch to 4-bit mode */
    HAL_Delay(1);

    /* Function set: 4-bit, 2 lines, 5x8 font */
    LCD_Command(0x28);
    /* Display control: display ON, cursor OFF, blink OFF */
    LCD_Command(0x0C);
    /* Entry mode set: increment cursor, no shift */
    LCD_Command(0x06);

    LCD_Clear();
    LCD_Home();
}
