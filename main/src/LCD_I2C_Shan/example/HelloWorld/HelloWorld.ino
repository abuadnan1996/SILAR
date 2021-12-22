#include<LCD_I2C_Shan.h>

LCD_I2C_Shan lcd(0x3F, 20, 4);

void setup(){
    lcd.init();
    lcd.println("    Hello");
    lcd.print("    World");
}

void loop(){

}
