#include <LiquidCrystal.h>

// Transmit rate in bps
#define TX_RATE 5

// Pin assignments
#define TX_CLOCK 2
#define TX_DATA 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_RS 8
#define LCD_EN 9
#define CRC_OUTPUT 10
#define CRC_READ 11
#define CRC_CLOCK 13

const char *message = "Hello, world!";

void setup() {
  pinMode(TX_CLOCK, OUTPUT);
  pinMode(TX_DATA, OUTPUT);
  pinMode(CRC_OUTPUT, INPUT);
  pinMode(CRC_READ, OUTPUT);
  pinMode(CRC_CLOCK, OUTPUT);

  digitalWrite(CRC_READ, HIGH);

  // Initialize the LCD screen
  LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(message);

  // Transmit data
  for (int byte_idx = 0; byte_idx < strlen(message); byte_idx++) {
    char tx_byte = message[byte_idx];

    // Clear the second line of the display
    lcd.noCursor();
    lcd.setCursor(0, 1);
    lcd.print("        ");
    lcd.setCursor(byte_idx, 0);
    lcd.cursor();

    for (int bit_idx = 0; bit_idx < 8; bit_idx++) {
      bool tx_bit = tx_byte & (0x80 >> bit_idx);

      digitalWrite(TX_DATA, tx_bit);
      delay((1000 / TX_RATE) / 2);

      // Update the LCD
      lcd.noCursor();
      lcd.setCursor(bit_idx, 1);
      lcd.print(tx_bit ? "1" : "0");
      lcd.setCursor(byte_idx, 0);
      lcd.cursor();

      // Pulse clock
      digitalWrite(TX_CLOCK, HIGH);
      digitalWrite(CRC_CLOCK, HIGH);
      delay((1000 / TX_RATE) / 2);
      digitalWrite(TX_CLOCK, LOW);
      digitalWrite(CRC_CLOCK, LOW);
    }
  }

  // Fill the CRC circuit with 16 zeros
  digitalWrite(TX_DATA, LOW);
  for (int i = 0; i < 16; i += 1) {
    delay((1000 / TX_RATE) / 2);
    digitalWrite(CRC_CLOCK, HIGH);
    delay((1000 / TX_RATE) / 2);
    digitalWrite(CRC_CLOCK, LOW);
  }

  // Read CRC from CRC circuit and transmit it
  digitalWrite(CRC_READ, LOW);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i += 1) {
    lcd.print(digitalRead(CRC_OUTPUT) ? "1" : "0");
    digitalWrite(TX_DATA, digitalRead(CRC_OUTPUT));

    delay((1000 / TX_RATE) / 2);
    digitalWrite(CRC_CLOCK, HIGH);
    digitalWrite(TX_CLOCK, HIGH);
    delay((1000 / TX_RATE) / 2);
    digitalWrite(CRC_CLOCK, LOW);
    digitalWrite(TX_CLOCK, LOW);
  }

  digitalWrite(TX_DATA, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
