#include "LCD_I2C_Shan.h"

LCD_I2C_Shan::LCD_I2C_Shan(uint8_t lcdAdress, uint8_t numCols, uint8_t numRows)
    : lcd(lcdAdress, numCols, numRows){
    row = 0;
    col = 0;
}

void LCD_I2C_Shan::init(){
    lcd.begin();
    lcd.backlight();
    lcd.clear();
}

bool LCD_I2C_Shan::setPos(uint8_t newRow, uint8_t newCol){
    if(newRow >= 0 && newRow <= row_max && newCol >= 0 && newCol <= col_max){
        row = newRow;
        col = newCol;
        lcd.setCursor(col, row);
        return true;
    }

    return false;
}

bool LCD_I2C_Shan::newLine(){
    return setPos(row+1, 0);
}

void LCD_I2C_Shan::print(String& str){
    if((col+str.length()-1) <= col_max){
        lcd.print(str);
        col += str.length();
    } else{
        uint8_t strCurrentPos = col_max - col + 1;
        lcd.print(str.substring(0, strCurrentPos));
        uint8_t remainingLength = str.length() - strCurrentPos;
        col = col_max;
        while((strCurrentPos < str.length()) && newLine()){
            uint8_t substringEnd = strCurrentPos+col_max >= str.length() ? str.length() : strCurrentPos+col_max+1;
            lcd.print(str.substring(strCurrentPos, substringEnd));
            col += substringEnd - strCurrentPos;
            strCurrentPos = substringEnd;
        }
        if(col>col_max && !newLine()){
            col = col_max;
        }
    }
}

void LCD_I2C_Shan::modify(int value, uint8_t startCol, uint8_t numCells){
    clearRange(startCol, startCol+numCells-1);
    print(value);
}

void LCD_I2C_Shan::modify(int value){
    backSpace();
    print(value);
}

bool LCD_I2C_Shan::write(char ch){
    if(col <= col_max){
        lcd.write(ch);
        ++col;
        return true;
    }

    return false;
}

bool LCD_I2C_Shan::backSpace(){
    if(setPos(row, col-1)){
        write(' ');
        return setPos(row, col-1);
    }

    return false;
}

void LCD_I2C_Shan::backSpace(uint8_t times){
    for(uint8_t i=0; i<times; ++i){
        backSpace();
    }
}

void LCD_I2C_Shan::clear(){
    lcd.clear();
    row = 0;
    col = 0;
}

void LCD_I2C_Shan::clearRange(uint8_t startCol, uint8_t endCol){
    if((endCol+1) > startCol){
        if((endCol+1) > col_max){
            setPos(row, col_max);
            write(' ');
            setPos(row, col_max);
        } else{
            setPos(row, endCol+1);
        }
        while(col > startCol){
            backSpace();
        }
    }
}

void LCD_I2C_Shan::animateDot(uint8_t numOfDots, unsigned long totalTimeMillis, unsigned long gapTimeMillis){
    uint8_t dotCount = 0;
    totalTimeMillis += millis();
    while(millis() < totalTimeMillis){
        ++dotCount;
        write('.');
        delay(gapTimeMillis);
        if(dotCount >= numOfDots){
            clearRange(col-numOfDots, col-1);
            dotCount = 0;
            delay(gapTimeMillis);
        }
    }
}
