#include <Keypad.h>
#include <LiquidCrystal.h>
#define PIN_LED 13
#define PIN_LED_2 9

int Contrast = 70;

int nb_tours = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


String a;
String temperature;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};




byte rowPins[COLS] = {A5, A4, A3, A2};
byte colPins[ROWS] = {  A1, 10, 7, 8};

String cin = "";

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {

  analogWrite(6, Contrast);
  lcd.begin(16, 2);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);

  Serial.begin(9600) ;
  analogReference(INTERNAL);

}

void loop() {
  char customKey = customKeypad.getKey();
  int valeur_brute = analogRead(A0);

  float temperature_celcius = valeur_brute * (1.1 / 1023.0 * 100.0);
  int tmp = trunc(temperature_celcius);



  // Envoi la mesure au PC pour affichage et attends 250ms
  /*Serial.println(tmp);
    lcd.setCursor(12, 0);
    lcd.print(tmp);
    Serial.write(tmp);*/
  //delay(250);

  if (customKey) {
    Serial.write(customKey);


    if (customKey == '#')
    {
      lcd.setCursor(4, 1);
      lcd.print("Attendez SVP");
      cin = "";
    }
    else if (customKey == '*')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bienvenue!");
      lcd.setCursor(0, 1);
      lcd.print("CIN:");
      cin = "";

    }
    else
    {
      lcd.setCursor(6, 1);
      cin += customKey;
      lcd.print(cin);

    }



  }

  else
  {
    lcd.setCursor(12, 0);
    lcd.print(tmp);

    Serial.write(tmp / 10);

    Serial.write(tmp % 10);

    delay(3000);



  }
  /*Serial.println(tmp);
    lcd.setCursor(12, 0);
    lcd.print(tmp);
    Serial.write(tmp/10);
    delay(300);
    Serial.write(tmp%10);
    delay(300);*/

  lcd.setCursor(0, 0);

  if (Serial.available() > 0)
  {
    a = Serial.readString();
    if (a != "Acces Refuse")
    {

      lcd.print(a);
      delay(4000);
      lcd.clear();
      
      /*digitalWrite(PIN_LED, HIGH);
      delay(4000);
      digitalWrite(PIN_LED, LOW);
      lcd.print(a);
      for (int positionCounter = 0; positionCounter < 40; positionCounter++) {
        lcd.scrollDisplayLeft();
        delay(200);
        if (positionCounter == 39 && nb_tours != 3)
        {
          positionCounter = 0;
          nb_tours++;
        }

        if (nb_tours == 2)
        {
          lcd.clear();
          positionCounter = 40;
        }

      }*/

    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.clear();
      digitalWrite(PIN_LED_2, HIGH);
      delay(4000);
      digitalWrite(PIN_LED_2, LOW);
      lcd.print(a);
      delay(4000);
      lcd.clear();
    }



  }
  else
  {

    lcd.setCursor(0, 0);
    lcd.print("Bienvenue!");
    lcd.setCursor(0, 1);
    lcd.print("CIN:");
  }

}
