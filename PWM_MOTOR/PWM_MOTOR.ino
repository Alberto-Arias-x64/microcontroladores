int motor1=13;
int pot1=A0;
int val=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1,OUTPUT);
  pinMode(pot1,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  val=analogRead(pot1);
  analogWrite(motor1,val);
}
