/*
 * lcd_i2c.h
 *
 * I2C LCD driver (PCF8574 backpack) for STM32F401RE
 * Uses I2C1: PB6 = SCL, PB7 = SDA
 *
 * Works with 16x2 / 20x4 LCDs that have a PCF8574 I2C backpack.
 * Default I2C address is usually 0x27 or 0x3F (7-bit address).
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_

#include "stm32f4xx_hal.h"

/* ---- USER CONFIG ---- */
#define LCD_I2C_ADDR      (0x27 << 1)   /* Change to (0x3F << 1) if 0x27 doesn't work */
#define LCD_COLS          16
#define LCD_ROWS          2

/* Handle to the I2C peripheral used (set in main.c via lcd_init) */
extern I2C_HandleTypeDef hi2c1;

/* ---- PUBLIC API ---- */
void LCD_Init(void);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_SetCursor(uint8_t col, uint8_t row);
void LCD_SendString(char *str);
void LCD_SendChar(char c);
void LCD_Backlight(uint8_t state); /* 1 = on, 0 = off */

#endif /* INC_LCD_I2C_H_ */
