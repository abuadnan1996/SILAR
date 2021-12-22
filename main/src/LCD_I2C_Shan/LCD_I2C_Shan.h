#ifndef _LCD_I2C_SHAN_H_
#define _LCD_I2C_SHAN_H_
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

// Set the LCD address to 0x3f for a 16 chars and 2 line display
class LCD_I2C_Shan{
private:
    LiquidCrystal_I2C lcd;
    uint8_t row, col;
public:
    const uint8_t col_max = 19, row_max = 3;
    LCD_I2C_Shan(uint8_t lcdAdress, uint8_t numCols, uint8_t numRows);
    void init();
    bool setPos(uint8_t row, uint8_t col);
    bool newLine();
    void print(String&);
    void println(String& str){ print(str); newLine(); }
    template <class T> void print(T obj){ String str = String(obj); print(str); }
    template <class T> void println(T obj){ String str = String(obj); println(str); };
    void modify(int value, uint8_t startCol, uint8_t numCells);
    void modify(int value);
    bool backSpace();
    void backSpace(uint8_t times);
    void clearRange(uint8_t startCol, uint8_t endCol);
    void clear();
    bool write(char);
    void animateDot(uint8_t numOfDots, unsigned long totalTime, unsigned long gapTimeMillis = 1000);
    uint8_t getRow(){ return row; }
    uint8_t getCol(){ return col; }
    void createChar(uint8_t num, const uint8_t data[]){ lcd.createChar(num, data); }
};

#endif
