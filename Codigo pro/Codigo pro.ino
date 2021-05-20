#include <DHT.h>
DHT dht(12, 22);
int ledpin = 10;
void setup()
{
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
}
void loop()
{
 int temp = dht.readTemperature();
 int humedad = dht.readHumidity();
 Serial.print("la temeperatura es = ");
 Serial.println(temp);
 Serial.print("la humedad es = ");
 Serial.println(humedad);
   int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  if(voltage<1.8)
  {
    digitalWrite(10, HIGH);
  }
  else
  {
    digitalWrite(10, LOW); 
  }
 Serial.print("la lumen es = ");
 Serial.println(voltage);
}
