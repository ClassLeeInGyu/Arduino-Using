#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "MQ135.h"
#define RZERO 464.1045837402

int triggerPin = 10;
int echoPin = 9;
int TemHumi = 7;
MQ135 gasSensor = MQ135 (A0);

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(TemHumi, DHT11);

void setup()
{
  //pinMode(MQ135, INPUT);
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(TemHumi,INPUT);
  Serial.begin(9600);
  //float rzero = gasSensor.getRZero();
  //Serial.print("rzero:");
  //Serial.println(rzero, DEC);
  
  lcd.init();
  lcd.backlight();
  dht.begin();
  
}
void loop()
{
  float dataMQ135 = gasSensor.getPPM();
  float dataTemp = dht.readTemperature();
  float dataHumi = dht.readHumidity();
  float dataFeel = dht.computeHeatIndex(dataTemp, dataHumi, false);
  digitalWrite(triggerPin, LOW);
  digitalWrite(echoPin, LOW);
  digitalWrite(triggerPin,HIGH);
  delay(10);
  digitalWrite(triggerPin,LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance = duration / 29 / 2;
  int sodongho;
  if ( distance < 11 )
  {
    sodongho = 1;
  }     
  else{
   sodongho = 0; 
  }
  
  if ( sodongho == 1 )
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temper : ");
  lcd.print(dataTemp);
  lcd.setCursor(0,1);
  delay(1000);
  lcd.print("State :  ");
  if ( dataTemp >= 23 || dataTemp <= 27 )
  {
    lcd.print("Perfect");
  }
  else if ( dataTemp < 23 || dataTemp >= 17 )
  {
    lcd.print("Good");
  }
  else if ( dataTemp > 27 || dataTemp <= 29 )
  {
    lcd.print("Good");
  }
  else
  {
    lcd.print("Bad");
  }
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humi : ");
  lcd.print(dataHumi);
  lcd.setCursor(15,0);
  lcd.print("%");
  lcd.setCursor(0,1);
  delay(1000);
  lcd.print("State :  ");
  if ( dataHumi < 40 )
  {
    lcd.print("Perfect");
  }
  else if ( dataHumi < 70 )
  {
    lcd.print("Good");
  }
  else
  {
    lcd.print("Bad");
  }
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("FeelTemp : ");
  lcd.print(dataFeel);
  lcd.setCursor(0,1);
  lcd.print("Your Feeling");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CO2 : ");
  lcd.print(dataMQ135);
  lcd.setCursor(13,0);
  lcd.print("ppm");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("State : ");
  if ( dataMQ135 < 700 )
  {
    lcd.print("Perfect");
  }
  else if ( dataMQ135 < 1000 )
  {
    lcd.print("Good");
  }
  else
  {
    lcd.print("Bad");
  }
  delay(3000);
  lcd.clear();
  }
  else
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Come Here    ");
  lcd.setCursor(0,1);
  lcd.print("  <----------");
  }  
  } 
