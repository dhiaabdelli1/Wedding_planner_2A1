#include <LiquidCrystal.h>

int Contrast = 60;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


String a;




void setup()
{
  analogWrite(6, Contrast);
  lcd.begin(16, 2);

  Serial.begin(9600) ;


}
void loop()
{
  lcd.setCursor(0, 0);

  lcd.setCursor(0, 1);



  if (Serial.available() > 0)
  {
    a = Serial.readString();
    lcd.print(a);

    for (int positionCounter = 0; positionCounter < 36; positionCounter++) {
      // scroll one position right:
      lcd.scrollDisplayLeft();
      // wait a bit:
      delay(350);
      if (positionCounter=35)
        positionCounter=0;

    }
  }
}
/*#define PIN_LED1 11
  #define PIN_LED2 12
  #define pas 9

  char data;
  int x;

  void setup() {

  pinMode(PIN_LED2, OUTPUT);
  digitalWrite(PIN_LED2,LOW);

  pinMode(PIN_LED1, OUTPUT);
  analogWrite(PIN_LED1,0);
  Serial.begin(9600) ;
  x=0;
  }

  void loop() {
  if (Serial.available())
  {
    data=Serial.read();
    if (data=='1')
    {
      digitalWrite(PIN_LED2,HIGH);
      Serial.write('1');
    }
    else if (data == '0')
    {
      digitalWrite(PIN_LED2,LOW);
      Serial.write('0');
    }
    else if (data == '2')
    {
      if (x+pas<255)
        x=x+pas;
      analogWrite(PIN_LED1,x);
      Serial.write(x);
    }
    else if (data == '3')
    {
      if (x>pas)
        x=x-pas;
      else
        x=0;
      analogWrite(PIN_LED1,x);
    }
  }
  }*/
