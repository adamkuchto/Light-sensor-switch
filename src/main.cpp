/*
  C:\Users\Adam\Desktop\Arduino\temp_zmierzch
  tam jest oryginal
  Potenciometr na ledy to 220ohm
  

*/

#include <Arduino.h>

#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Timers.h>
#define ONE_WIRE_BUS 2
#define czujnik (A1)
#define led (A0)
#define potencjometr (A2)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x20, 16, 2);
unsigned long long czas = 0;  // czas z funkcji millis()
unsigned long long uplyw = 0; // czas dodatkowy tymczas
int pot, czuj, war;
/**
 * funkcja odczytujaca dane wejsciowe 
 * w czasie "millis"
 */
void odczyt()
{
    czas = millis();
    const long przerwa = 1000;

    if (czas - uplyw >= przerwa) // instrukcja
    {
        uplyw = czas;
        pot = analogRead(potencjometr);
        czuj = analogRead(czujnik);
        war = pot + czuj;
    }
}

void setup()
{
    Serial.begin(9600);
    sensors.begin();
    lcd.init();
    lcd.backlight();
    //**********
    pinMode(13, OUTPUT); //swiatlo
    pinMode(A0, INPUT_PULLUP);
    pinMode(5, OUTPUT);
    pinMode(10, INPUT_PULLUP);
}

/**
 * funkcja włączająca światło
 */ 
void switcher()
{
    if (war > 900) // tutaj ustaw! // druga zmiana 1200
    {

        digitalWrite(13, 1);
    }
    else
    {
        digitalWrite(13, 0);
    }
}
void loop()
{
    odczyt();
    switcher();
    Serial.print(war);
    Serial.print("\t");
    Serial.print(pot);
    Serial.print("\t");
    Serial.println(czuj);

    sensors.requestTemperatures();
    // Serial.print(sensors.getTempCByIndex(0)); //dokladnosc wyswietlania temp
    // Serial.println("C");
    // delay(500);

    lcd.setCursor(2, 0);
    lcd.print("TEMPERATURA:");
    lcd.setCursor(2, 1);
    lcd.print(sensors.getTempCByIndex(0), 1);
    lcd.setCursor(9, 1);
    lcd.print("st. C");
    //******************


    delay(100);
}