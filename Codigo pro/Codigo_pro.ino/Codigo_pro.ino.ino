#include <DHT.h>
DHT dht(12, 22);  // Pin 12 de lectura del sensor
int ledpin = 10;  // Salida hacia transistor de control de leds
int fn1 = 2;      // Final de carrera techo cerrado
int fn2 = 3;      // Final de carrera techo abierto
int mt1a = 4;     // Motor del techo pulso de apertura
int mt1b = 5;     // Motor del techo pulso de cierre
int mt2 = 6;      // Motor de ventilador
int mt3 = 7;      // Motor de bomba de agua 
int i;            // Variable cuenta tiepo en 1/100 sec
int n;            // Segunda variable de tiempo 1/100 sec
void setup()
{
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  pinMode(fn1, INPUT);
  pinMode(fn2, INPUT);
  pinMode(mt1a, OUTPUT);
  pinMode(mt1b, OUTPUT);
  pinMode(mt2, OUTPUT);
  i=0;
  n=0;
}
void loop()
{
 float temp = dht.readTemperature();
 float humedad = dht.readHumidity();
 float sensorValue = analogRead(A0);
 float voltage = sensorValue * (5.0 / 1023.0);
 int opn = digitalRead(fn1);
 int cls = digitalRead(fn2);
 delay(10);
 i=i+1;
 n=n+1;
 if(voltage<4)                  // Luz para cerrar el techo
  {
    while(opn != HIGH)
    {
      digitalWrite (mt1b, HIGH);
      opn = digitalRead(fn1);
    }
    digitalWrite(mt1b, LOW);
    if(voltage<1.2 && i>=500)    // Prende las luces con un retardo de 5 seg
    {
      digitalWrite(10, HIGH);
      i=0;
    }
    else if(voltage>1.2 && i>=500) // Apaga las luces con un retardo de 5 sec
    {
      digitalWrite(10, LOW);
      i=0;
    }
  }
  else if(voltage>4)      // Luz para abrir el techo
  {
    while(cls != HIGH)
    {
      digitalWrite (mt1a, HIGH);
      cls = digitalRead(fn2);
    }
    digitalWrite (mt1a, LOW);
  }
  if(n >= 1000)   // Temperatura y humedad cada 10 segundos
  {
    if(temp >= 23)
    {
      digitalWrite(6, HIGH);   // Prende ventilador
      n=0;
      if(humedad < 50.00)
      {
        digitalWrite(7, HIGH);  // Prende motor humedad
        delay(5000);             // Riega 5 segundos
      }
      digitalWrite(7, LOW);   // Apaga el motor
    }
    else if(temp < 23)
    {
      digitalWrite(6, LOW);    // Apaga ventilador
      n=0;
      if(humedad < 50.00)
      {
        digitalWrite(7, HIGH);  // Prende motor humedad
        delay(2000);             // Riega 2 segundos
      }
      digitalWrite(7, LOW);   // Apaga el motor
    }
   Serial.println(temp);
   Serial.println(humedad);
  }
}

