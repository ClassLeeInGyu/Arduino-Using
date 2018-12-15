#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

int triggerPin = 10;
int echoPin = 9;
int MQ135 = A0;
int TemHumi = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(TemHumi, DHT11);

void setup()
{
  pinMode(MQ135, INPUT);
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);

  lcd.init();
  lcd.backlight();
  dht.begin();
  
}

void loop()
{
  int dataMQ135 = analogRead(MQ135);
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
  
  if( distance < 10 )
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temper : ");
  lcd.print(dataTemp);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("State : ");
  if (dataTemp < 24 || dataTemp > 27)
  {
    lcd.print("Good");
  }
  else if (dataTemp < 27 || dataTemp > 24)
  {
    lcd.print("Perfect");
  }
  else
  {
    lcd.print("Bad");
  }
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Humi : ");
  lcd.print(dataHumi);
  lcd.setCursor(15,0);
  lcd.print("%");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("State : ");
  if (dataHumi < 30)
  {
    lcd.print("Perfect");
  }
  else if (dataHumi < 60)
  {
    lcd.print("Good");
  }
  else
  {
    lcd.print("Bad");
  }
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("FeelTemp : ");
  lcd.print(dataFeel);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Made By Lee");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("CO2 : ");
  lcd.print(dataMQ135);
  lcd.setCursor(13,0);
  lcd.print("ppm");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("State : ");
  if (dataHumi < 300)
  {
    lcd.print("Perfect");
  }
  else if (dataHumi < 500)
  {
    lcd.print("Good");
  }
  else
  {
    lcd.print("Bad");
  }
  delay(2000);
  lcd.clear();
  }
  else
  {
    lcd.clear();
  }
}
