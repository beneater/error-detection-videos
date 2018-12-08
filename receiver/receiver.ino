#include <LiquidCrystal.h>

// Pin assignments
#define RX_CLOCK 2
#define RX_DATA 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_RS 8
#define LCD_EN 9

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

char message[16];
volatile byte rx_byte = 0;
volatile int bit_position = 0;
volatile bool update_lcd = true;

void setup() {
  pinMode(RX_DATA, INPUT);
  strcpy(message, "");
  lcd.begin(16, 2);
  attachInterrupt(digitalPinToInterrupt(RX_CLOCK), onClockPulse, RISING);
}

void onClockPulse() {
  bool rx_bit = digitalRead(RX_DATA);

  if (bit_position == 8) {
    rx_byte = 0;
    bit_position = 0;
  }
  
  if (rx_bit) {
    rx_byte |= (0x80 >> bit_position);
  }

  bit_position += 1;

  if (bit_position == 8) {
    strncat(message, (const char *)&rx_byte, 1);
  }
  
  update_lcd = true;
}

void loop() {
  if (update_lcd) {
    update_lcd = false;
    
    lcd.noCursor();
    lcd.setCursor(0, 0);
    lcd.print(message);
    lcd.setCursor(0, 1);
    for (int i = 0; i < 8; i += 1) {
      if (i < bit_position) {
        lcd.print(rx_byte & (0x80 >> i) ? "1" : "0");
      } else {
        lcd.print(" ");
      }
    }
    lcd.setCursor(strlen(message), 0);
    lcd.cursor();
  }
}
