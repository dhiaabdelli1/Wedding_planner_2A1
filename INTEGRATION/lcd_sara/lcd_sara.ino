#include <Keypad.h>
#include <LiquidCrystal.h>


int Contrast = 70;

int nb_tours = 0;

LiquidCrystal lcd(8, 7, 5, 4, 3, 2);

//12 --> 8 11 --> A0 


void setup() {
  // put your setup code here, to run once:
  analogWrite(6, Contrast);
  Serial.begin(9600) ;

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(4, 1);
  lcd.print("Fuck");

}
