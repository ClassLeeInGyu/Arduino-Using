#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(TemHumi, DHT11);

int MQ135 = A0;
int MQ8 = A1;
int MQ7 = A2;
int TemHumi = 4;



void setup()
{
 
pinMode(MQ135,INPUT); // 이산화탄소 검출
pinMode(MQ8,INPUT); // 수소 문제발생
pinMode(MQ7,INPUT); // 일산화탄소 검출 과열문제

lcd.begin();
dht.begin();
 
Serial.begin(9600);

}



void loop()
{
 
int dataMQ135 = analogRead(MQ135); // 이산화탄소
int dataMQ8 = analogRead(MQ8); // 수소
int dataMQ7 = analogRead(MQ7); // 일산화탄소
float dataTemp = dht.readTemperature(); // 온도
float dataHumi = dht.readHumidity(); // 습도
float dataFeel = dht.computeHeatIndex(dataTemp, dataHumi, false); // 체감온도

lcd.setCursor(0,0);
lcd.print("Temper : ");
lcd.print(dataTemp);
delay(1000);
lcd.setCursor(0,1);
lcd.print("State : ");
lcd.print("Perfect");
delay(2000);
lcd.clear();

lcd.setCursor(0,0);
lcd.print("FeelTemp : ");
lcd.print(dataFeel);
delay(1000);
lcd.setCursor(0,1);
lcd.print("State : ");
lcd.print("Perfect");
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
lcd.print("Perfect");
delay(2000);
lcd.clear();

lcd.setCursor(0,0);
lcd.print("CO2 : ");
lcd.print(dataMQ135);
lcd.setCursor(13,0);
0lcd.print("ppm");
delay(1000);
lcd.setCursor(0,1);
lcd.print("State : ");
lcd.print("Perfect");
delay(2000);
lcd.clear();

lcd.setCursor(0,0);
lcd.print("H2 : ");
lcd.print(dataMQ8);
lcd.setCursor(13,0);
lcd.print("ppm");
delay(1000);
lcd.setCursor(0,1);
lcd.print("State : ");
lcd.print("Perfect");
delay(2000);
lcd.clear();

lcd.setCursor(0,0);
lcd.print("CO : ");
lcd.print(dataMQ7);
lcd.setCursor(13,0);
lcd.print("ppm");
delay(1000);
lcd.setCursor(0,1);
lcd.print("State : ");
lcd.print("Perfect");
delay(2000);
lcd.clear();

}
